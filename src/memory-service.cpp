#include <string>
#include <vector>
#include <iostream>
#include "memory-service.h"
#include "split.h"

void MemoryService::add(Item item) {
    if (this->items.find(item.id) != this->items.end()) {
        return;
    }
    this->items[item.id] = item;

    std::vector<std::string> words = split(item.data, ' ');
    for (size_t i = 0; i < words.size(); i++) {
        auto found = this->tokens.find(words[i]);
        if (found == this->tokens.end()) {
            std::unordered_set<std::string> set;
            set.insert(item.id);
            this->tokens.insert(std::make_pair(words[i], set));
        } else {
            found->second.insert(item.id);
        }
    }
}

void MemoryService::del(const std::string &id) {
}

std::vector<std::string> MemoryService::query(Query query) {
    return std::vector<std::string>();
}

void MemoryService::status() {
    std::cout << "Status" << std::endl;

    std::cout << "\tItems: {";
    for (auto it = this->items.begin(); it != this->items.end(); it++) {
        if (it != this->items.begin()) {
            std::cout << ", ";
        }
        std::cout << it->first;
    }
    std::cout << "}" << std::endl;

    std::cout << "\tToken Sets: {" << std::endl;

    for (auto it = this->tokens.begin(); it != this->tokens.end(); it++) {
        std::cout << "\t\t" << it->first << ": {";
        for (auto id = it->second.begin(); id != it->second.end(); id++) {
            if (id != it->second.begin()) {
                std::cout << ", ";
            }
            std::cout << *id;
        }
        std::cout << "}" << std::endl;
    }
    std::cout << "\t}" << std::endl;
}
