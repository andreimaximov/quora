#include "memory-service.h"
#include "split.h"

bool MemoryService::Result::operator<(const Result &other) const {
    if (this->score < other.score) {
        return false;
    } else if (this->score == other.score) {
        return this->time > other.time;
    }
    return true;
}

MemoryService::Traverser::Traverser(
    const Query &query,
    const MemoryService &memoryService) :
    query(query),
    memoryService(memoryService) {
}

bool MemoryService::Traverser::matches(const Entry &entry) {
    for (const std::string &token : this->query.tokens) {
        if (!entry.trie.contains(token)) {
            return false;
        }
    }
    return true;
}

float MemoryService::Traverser::score(const Entry &entry) {
    float score = entry.score;

    auto typeIter = this->query.typeBoosts.find(entry.type);
    if (typeIter != this->query.typeBoosts.end()) {
        score *= typeIter->second;
    }

    auto idBoost = this->query.idBoosts.find(entry.id);
    if (idBoost != this->query.idBoosts.end()) {
        score *= idBoost->second;
    }

    return score;
}

void MemoryService::Traverser::operator()(const std::string &candidate) {
    const auto iter = this->memoryService.items.find(candidate);
    if (iter == this->memoryService.items.end()) {
        return;
    }

    const MemoryService::Entry &entry = iter->second;
    if (!this->matches(entry)) {
        return;
    }

    if (this->cache.find(candidate) != this->cache.end()) {
        return;
    }
    this->cache.emplace(candidate);

    Result result {candidate, this->score(entry), entry.time};

    if (this->heap.size() >= this->query.results &&
        this->heap.top() < result) {
        return;
    }

    this->heap.push(std::move(result));
    if (this->heap.size() > this->query.results) {
        this->heap.pop();
    }
}

std::vector<std::string> MemoryService::Traverser::results() {
    size_t i = this->heap.size();
    std::vector<std::string> results(i);

    while ((i--) > 0) {
        results[i] = this->heap.top().id;
        this->heap.pop();
    }

    return results;
}

uint32_t MemoryService::time = 0;

MemoryService::MemoryService(std::ostream &os) : out(os) {
}

void MemoryService::add(const Item &item) {
    if (this->items.find(item.id) != this->items.end()) {
        return;
    }

    Entry entry {item.id, item.type, item.score, MemoryService::time++};

    std::string body = item.body;
    std::transform(body.begin(), body.end(), body.begin(), ::tolower);

    for (std::string &str : split(body, ' ')) {
        entry.trie.insert(str);
    }

    for (std::string &tail : entry.trie.tails()) {
        this->prefixes.insert(tail, item.id);
    }

    this->items[item.id] = std::move(entry);
}

void MemoryService::del(const std::string &id) {
    if (this->items.find(id) == this->items.end()) {
        return;
    }

    MemoryService::Entry &entry = this->items[id];

    for (std::string &tail : entry.trie.tails()) {
        this->prefixes.erase(tail, id);
    }

    this->items.erase(id);
}

std::vector<std::string> MemoryService::query(Query query) {
    if (query.results == 0) {
        return std::vector<std::string>();
    }

    std::string bucket = "";
    if (query.tokens.size() > 0) {
        bucket = query.tokens.back();
        query.tokens.pop_back();
    }

    MemoryService::Traverser traverser(query, *this);
    this->prefixes.each(traverser, bucket);

    return traverser.results();
}

void MemoryService::status() {
    this->out << "Status" << std::endl;

    this->out << "\tItems: {";
    std::string separator = "";
    for (auto &pair : this->items) {
        this->out << separator << pair.first;
        separator = ", ";
    }
    this->out << "}" << std::endl;
}
