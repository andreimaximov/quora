#include <unordered_set>
#include <queue>
#include "typeahead.hpp"
#include "intersection.hpp"

void Typeahead::add(const Item& item) {
  auto it = this->items.find(item.id);
  if (it != this->items.end()) {
    return;
  }
  this->items[item.id] = item;
  Item& copy = this->items[item.id];
  copy.order = order++;
  for (const std::string& token : copy.tokens) {
    this->prefixes.insert(std::make_pair(token, &copy));
  }
}

void Typeahead::del(const std::string& id) {
  auto it = this->items.find(id);
  if (it == this->items.end()) {
    return;
  }

  Item& item = it->second;
  for (const std::string& token : item.tokens) {
    this->prefixes.erase(std::make_pair(token, &item));
  }

  this->items.erase(id);
}

size_t Typeahead::getSmallestPrefixSet(const Query& query) {
  size_t index = 0;
  size_t size = this->prefixes[query.tokens[0]].size();
  for (size_t i = index + 1; i != query.tokens.size(); i++) {
    const auto& candidate = this->prefixes[query.tokens[i]];
    if (candidate.size() < size) {
      index = i;
    }
  }
  return index;
}

std::vector<const Item*> Typeahead::getTopItems(const Query& query,
    const std::unordered_set<Item*> items) {
  // Extract the top items from the set
  std::priority_queue<Candidate> queue;
  for (auto it = items.begin(); it != items.end(); ++it) {
    double score = query.scoreItem(**it);
    queue.push(Candidate {*it, score});
    if (queue.size() > query.results) {
      queue.pop();
    }
  }

  // Insert into vector in reverse order because the queue holds the lowest
  // scoring item at the top.
  std::vector<const Item*> results(queue.size());
  size_t i = results.size() - 1;
  while (!queue.empty()) {
    results[i--] = queue.top().item;
    queue.pop();
  }
  return results;
}

std::vector<const Item*> Typeahead::query(const Query& query) {
  if (query.results == 0 || query.tokens.empty()) {
    return std::vector<const Item*>();
  }

  size_t index = this->getSmallestPrefixSet(query);
  std::unordered_set<Item*> intersect = this->prefixes[query.tokens[index]];

  for (size_t i = 0; i != query.tokens.size(); i++) {
    if (i == index) continue;
    const std::string& token = query.tokens[i];
    const std::unordered_set<Item*>& candidates = this->prefixes[token];
    intersect = intersection<Item*>(intersect, candidates);
  }

  return this->getTopItems(query, intersect);
}

bool operator<(const Candidate& lhs, const Candidate& rhs) {
  if (lhs.score != rhs.score) {
    return rhs.score < lhs.score;
  }
  return rhs.item->order < lhs.item->order;
}
