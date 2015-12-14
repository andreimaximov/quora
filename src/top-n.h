#include <vector>
#include <queue>

#ifndef SRC_TOP_N_H_
#define SRC_TOP_N_H_

template<class E>
std::vector<E> topn(std::vector<E> &elements, size_t n) { // NOLINT
    std::priority_queue<E, std::vector<E>, std::greater<E>> q;
    for (const E &elem : elements) {
        q.push(elem);
        if (q.size() > n) {
            q.pop();
        }
    }

    std::vector<E> results;
    while (q.size() > 0) {
        results.push_back(q.top());
        q.pop();
    }
    return results;
}

#endif  // SRC_TOP_N_H_
