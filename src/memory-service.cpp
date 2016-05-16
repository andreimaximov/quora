#include "memory-service.h"

MemoryService::Entry::Entry(const Item& item, uint32_t time) :
  item(item), time(time) {
}

bool MemoryService::Result::operator<(const Result& other) const {
  if (this->score < other.score) {
    return false;
  } else if (this->score == other.score) {
    return this->time > other.time;
  }
  return true;
}

MemoryService::Collector::Collector(
  const Query& query,
  const MemoryService& memoryService) :
  query(query),
  memoryService(memoryService) {
  this->init();
}

void MemoryService::Collector::init() {
  for (const IDBoost& boost : this->query.idBoosts) {
    auto find = this->memoryService.items.find(boost.id);
    if (find == this->memoryService.items.end()) {
      continue;
    }
    this->process(*find->second, boost.boost);
  }
}

bool MemoryService::Collector::matches(const Entry& entry) {
  for (const std::string& token : this->query.tokens) {
    if (!entry.prefixes.contains(token)) {
      return false;
    }
  }
  return true;
}

void MemoryService::Collector::operator()(const Entry::shared_ptr& entry) {
  this->process(*entry, 1);
}

void MemoryService::Collector::process(const Entry& entry, float boost) {
  if (!this->matches(entry)) {
    return;
  }

  if (this->cache.find(entry.item.id) != this->cache.end()) {
    return;
  }
  this->cache.emplace(entry.item.id);

  boost *= this->query.typeBoosts[entry.item.type];
  Result result {entry.item.id, entry.item.score * boost, entry.time};

  if (this->heap.size() >= this->query.results &&
  this->heap.top() < result) {
    return;
  }

  this->heap.push(std::move(result));
  if (this->heap.size() > this->query.results) {
    this->heap.pop();
  }
}

std::vector<std::string> MemoryService::Collector::results() {
  size_t i = this->heap.size();
  std::vector<std::string> results(i);

  while ((i--) > 0) {
    results[i] = this->heap.top().id;
    this->heap.pop();
  }

  return results;
}

MemoryService::MemoryService() : time(0) {
}

void MemoryService::add(const Item& item) {
  if (this->items.find(item.id) != this->items.end()) {
    return;
  }

  std::shared_ptr<Entry> entry(new Entry(item, this->time++));

  for (const std::string& token : entry->item.tokens) {
    entry->prefixes.insert(token);
    this->prefixes.insert(std::make_pair(token, entry));
  }

  this->items[item.id] = entry;
}

void MemoryService::del(const std::string& id) {
  auto iter = this->items.find(id);
  if (iter == this->items.end()) {
    return;
  }

  Entry::shared_ptr entry = iter->second;

  for (const std::string& token : entry->item.tokens) {
    this->prefixes.erase(std::make_pair(token, entry));
  }

  this->items.erase(id);
}

std::vector<std::string> MemoryService::query(const Query& query) {
  if (query.results == 0) {
    return std::vector<std::string>();
  }

  MemoryService::Collector collector(query, *this);

  std::string bucket("");
  if (!query.tokens.empty()) {
    bucket = query.tokens.back();
  }
  this->prefixes.each(collector, bucket);

  return collector.results();
}
