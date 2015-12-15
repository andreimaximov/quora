#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <queue>
#include <stack>
#include "memory-service.h"
#include "split.h"

template <class T>
using rp_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;

MemoryService::MemoryService(std::ostream &os) : out(os) {
}

void MemoryService::add(Item item) {
    if (this->items.find(item.id) != this->items.end()) {
        return;
    }

    std::transform(
        item.data.begin(),
        item.data.end(),
        item.data.begin(),
        ::tolower);

    ItemEntry entry {item};

    std::vector<std::string> tokens = split(item.data, ' ');
    for (const std::string &str : tokens) {
        entry.trie.insert(str);
        this->trieSet.insert(str, item.id);
    }

    this->items[item.id] = std::move(entry);
}

void MemoryService::del(const std::string &id) {
    if (this->items.find(id) == this->items.end()) {
        return;
    }

    ItemEntry &entry = this->items[id];

    std::vector<std::string> tokens = split(entry.item.data, ' ');
    for (std::string &word : tokens) {
        this->trieSet.erase(word, id);
    }

    this->items.erase(id);
}

bool MemoryService::match(const ItemEntry &itemEntry, const Query &query) {
    for (const std::string &token : query.tokens) {
        if (!itemEntry.trie.contains(token)) {
            return false;
        }
    }
    return true;
}

std::vector<std::string> MemoryService::query(Query query) {
    TrieSet<std::string>::Node *node = this->trieSet.get_prefix_node(
        query.tokens.back());
    query.tokens.pop_back();

    if (node == nullptr) {
        return std::vector<std::string>(0);
    }

    rp_queue<std::pair<std::string, double>> results_queue;
    std::unordered_set<std::string> results_set;
    std::stack<TrieSet<std::string>::Node*> stack;
    stack.push(node);

    while (stack.size() > 0) {
        auto node = stack.top();
        stack.pop();
        for (const std::string &str : node->elements) {
            if (results_set.find(str) != results_set.end()) {
                continue;
            }

            ItemEntry &itemEntry = this->items[str];
            if (this->match(itemEntry, query)) {
                results_set.insert(str);

                double score = itemEntry.item.score;

                ItemType type = itemEntry.item.type;
                if (query.typeBoosts.find(type) != query.typeBoosts.end()) {
                    score *= query.typeBoosts[type];
                }

                if (query.idBoosts.find(str) != query.idBoosts.end()) {
                    score *= query.idBoosts[str];
                }

                results_queue.push(std::make_pair(str, score));
                if (results_queue.size() > query.results) {
                    results_queue.pop();
                }
            }
        }
        for (const auto &entry : node->children) {
            stack.push(entry.second);
        }
    }

    std::vector<std::string> results(results_queue.size());
    size_t i = results.size();
    while ((i--) > 0) {
        results[i] = results_queue.top().first;
        results_queue.pop();
    }

    return results;
}

void MemoryService::status() {
    this->out << "Status" << std::endl;

    this->out << "\tItems: {";
    for (auto it = this->items.begin(); it != this->items.end(); it++) {
        if (it != this->items.begin()) {
            this->out << ", ";
        }
        this->out << it->first;
    }
    this->out << "}" << std::endl;
}
