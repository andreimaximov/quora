#!/usr/bin/env python

import sys


def read(fn):
    return [fn(x) for x in sys.stdin.readline().split()]


def matrix(n, m):
    """
    Creates an n x m matrix.
    """
    return [[None for i in range(0, m)] for j in range(0, n)]


def range_lengths(upvotes, comparator):
    n = len(upvotes)
    start = 0
    lengths = matrix(2, n)
    for i in range(0, n):
        if i < n - 1 and comparator(upvotes[i], upvotes[i + 1]):
            continue
        length = i - start + 1
        for j in range(start, i + 1):
            lengths[0][j] = length - (j - start)
            lengths[1][j] = j - start + 1
        start = i + 1
    return lengths


def preprocess(upvotes):
    cache = [None] * 5
    nd = range_lengths(upvotes, lambda lhs, rhs: lhs <= rhs)
    cache[0] = nd[0]
    cache[1] = nd[1]
    ni = range_lengths(upvotes, lambda lhs, rhs: lhs >= rhs)
    cache[2] = ni[0]
    cache[3] = ni[1]
    cache[4] = [0 for i in range(0, len(upvotes))]
    return cache


def metric_for_window(upvotes, cache, i, k):
    """
    Calculates metric for window of length k ending at index i.
    """
    assert i >= 0
    assert i < len(upvotes)

    lo = i - k + 1
    hi = i

    metric = 0 if i == 0 else cache[4][i - 1]

    if lo > 0:
        metric -= (min(k, cache[0][lo - 1]) - min(k, cache[2][lo - 1]))

    if hi > 0:
        metric += (min(k, cache[1][hi]) - min(k, cache[3][hi]))

    cache[4][i] = metric
    return metric


def main():
    (N, K) = read(int)
    upvotes = read(int)

    cache = preprocess(upvotes)

    for i in range(1, K - 1):
        metric_for_window(upvotes, cache, i, i + 1)

    for i in range(K - 1, len(upvotes)):
        print(metric_for_window(upvotes, cache, i, K))

if __name__ == '__main__':
    main()
