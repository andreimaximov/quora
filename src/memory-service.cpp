#include <string>
#include <vector>
#include <iostream>
#include "memory-service.h"
#include "split.h"

MemoryService::MemoryService(std::ostream &os) : out(os) {
}

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
    this->out << "Status" << std::endl;

    this->out << "\tItems: {";
    for (auto it = this->items.begin(); it != this->items.end(); it++) {
        if (it != this->items.begin()) {
            this->out << ", ";
        }
        this->out << it->first;
    }
    this->out << "}" << std::endl;

    this->out << "\tToken Sets: {" << std::endl;

    for (auto it = this->tokens.begin(); it != this->tokens.end(); it++) {
        this->out << "\t\t" << it->first << ": {";
        for (auto id = it->second.begin(); id != it->second.end(); id++) {
            if (id != it->second.begin()) {
                this->out << ", ";
            }
            this->out << *id;
        }
        this->out << "}" << std::endl;
    }
    this->out << "\t}" << std::endl;
}
