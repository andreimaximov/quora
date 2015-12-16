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
    Query *query,
    MemoryService *memoryService) {
    this->query = query;
    this->memoryService = memoryService;
}

bool MemoryService::Traverser::matches(const Entry &entry) {
    for (const std::string &token : this->query->tokens) {
        if (!entry.trie.contains(token)) {
            return false;
        }
    }
    return true;
}

double MemoryService::Traverser::score(const Entry &entry) {
    double score = entry.score;

    auto tboost = this->query->typeBoosts.find(entry.type);
    if (tboost != this->query->typeBoosts.end()) {
        score *= tboost->second;
    }

    auto iboost = this->query->idBoosts.find(entry.id);
    if (iboost != this->query->idBoosts.end()) {
        score *= iboost->second;
    }

    return score;
}

void MemoryService::Traverser::operator()(const std::string &candidate) {
    if (this->encountered.find(candidate) != this->encountered.end()) {
        return;
    }

    this->encountered.insert(candidate);

    MemoryService::Entry &entry = this->memoryService->items[candidate];
    if (!this->matches(entry)) {
        return;
    }

    double score = this->score(entry);

    Result result {candidate, score, entry.time};

    if (this->heap.size() >= this->query->results &&
        this->heap.top() < result) {
        return;
    }

    this->heap.push(std::move(result));
    if (this->heap.size() > this->query->results) {
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

MemoryService::MemoryService(std::ostream &os) : out(os) {
}

void MemoryService::add(const Item &item) {
    if (this->items.find(item.id) != this->items.end()) {
        return;
    }

    MemoryService::Entry entry {item.id, item.type, item.score, item.time};

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
    std::vector<std::string> results;
    if (query.results == 0) {
        return results;
    }

    std::string bucket = "";
    if (query.tokens.size() > 0) {
        bucket = query.tokens.back();
        query.tokens.pop_back();
    }

    MemoryService::Traverser traverser(&query, this);
    this->prefixes.traverse(traverser, bucket);

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
