#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <ctype.h>
#include "memory-service.h"
#include "split.h"
#include "top-n.h"

MemoryService::MemoryService(std::ostream &os) : out(os) {
}

void MemoryService::add(Item item) {
    if (this->items.find(item.id) != this->items.end()) {
        return;
    }

    std::vector<std::string> tokens = split(item.data, ' ');
    for (std::string &str : tokens) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

    ItemEntry entry {
        item,
        tokens
    };
    this->items[item.id] = entry;

    for (std::string &word : entry.tokens) {
        this->trie.add(word, item.id);
    }
}

void MemoryService::del(const std::string &id) {
    if (this->items.find(id) == this->items.end()) {
        return;
    }

    ItemEntry &entry = this->items[id];

    for (std::string &word : entry.tokens) {
        this->trie.erase(word, id);
    }

    this->items.erase(id);
}

std::vector<std::string> MemoryService::query(Query query) {
    std::unordered_map<std::string, int> counts;
    for (std::string &token : query.tokens) {
        std::unordered_set<std::string> ids = this->trie.get_prefix_set(token);
        for (auto &id : ids) {
            if (counts.find(id) == counts.end()) {
                counts[id] = 0;
            }
            counts[id] += 1;
        }
    }

    std::vector<std::pair<std::string, double>> candidates;

    for (auto &pair : counts) {
        if (pair.second < query.tokens.size()) {
            continue;
        }
        Item &item = this->items[pair.first].item;
        double score = item.score;
        if (query.typeBoosts.find(item.type) != query.typeBoosts.end()) {
            score *= query.typeBoosts[item.type];
        }
        if (query.idBoosts.find(item.id) != query.idBoosts.end()) {
            score *= query.idBoosts[item.id];
        }
        candidates.push_back(std::make_pair(item.id, score));
    }

    candidates = std::move(topn(candidates, query.results));

    std::vector<std::string> results;
    for (auto it = candidates.rbegin(); it != candidates.rend(); it++) {
        results.push_back(it->first);
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

    this->out << "\tTrie Size: " << this->trie.size() << std::endl;

    this->out << "\tTrie: " << this->trie << std::endl;
}
