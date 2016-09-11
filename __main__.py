#!/usr/bin/env python

import sys


def read(fn):
    return [fn(x) for x in sys.stdin.readline().split()]


def matrix(n, m):
    """
    Creates an n x m matrix.
    """
    return [[None for i in range(0, m)] for j in range(0, n)]


def ranges(upvotes, compare):
    """
    Creates 2 x len(upvotes) matrix representing the distance from each index
    to the start and end of the range each index is in such that a < b,
    a <= i < j <= b, and compare(upvotes[i], upvotes[j]) for range [a, b].

    For example, say the comparator matches non-decreasing pairs of integers
    and we are given the upvotes array [4, 5, 6, 7, 3]. This will return the
    following matrix.

    [1, 2, 3, 4, 1]
    [4, 3, 2, 1, 1]

    For example, index 2 with value 6 is part of range [0, 3]. There are 3
    values {4, 5, 6} between 6 (inclusive) and the start of the range.
    Similarly, there are 2 values {6, 7} between 6 (inclusive) and the end of
    the range.
    """
    n = len(upvotes)
    start = 0
    lengths = matrix(2, n)
    for i in range(0, n):
        # Continue if still in range and comparison holds.
        if i < n - 1 and compare(upvotes[i], upvotes[i + 1]):
            continue

        # Comparison no longer holds. Length of this range.
        length = i - start + 1

        # Update distance for all values in range.
        for j in range(start, i + 1):
            # Distance from j to end of range including j.
            lengths[0][j] = length - (j - start)
            # Distance from start of range to j including j.
            lengths[1][j] = j - start + 1

        # Update start of next range.
        start = i + 1
    return lengths


def preprocess(upvotes):
    """
    Calculates a 5 x len(upvotes) matrix that caches information about upvotes.
    """
    cache = [None] * 5

    # Cache info about non-decreasing ranges.
    nd = ranges(upvotes, lambda lhs, rhs: lhs <= rhs)
    cache[0] = nd[0]
    cache[1] = nd[1]

    # Calculate info about non-increasing ranges.
    ni = ranges(upvotes, lambda lhs, rhs: lhs >= rhs)
    cache[2] = ni[0]
    cache[3] = ni[1]

    # Will hold metrics for each window ending at each index.
    cache[4] = [0 for i in range(0, len(upvotes))]
    return cache


def metric_for_window(upvotes, cache, i, k):
    """
    Calculates metric for window of length k ending at index i.
    """
    assert i >= 0
    assert i < len(upvotes)

    lo = i - k + 1  # First index in the window
    hi = i  # Last index in the window

    # Use metric from previous window as a base
    metric = 0 if i == 0 else cache[4][i - 1]

    # Subtract the metric from the previous window but only for sub-ranges
    # starting at the FIRST index of the previous window. This is because the
    # first index from the last window is no longer part of the current window.
    if lo > 0:
        # If the range is longer than window K, count only the first K values.
        metric -= (min(k, cache[0][lo - 1]) - min(k, cache[2][lo - 1]))

    # Add the metric counting only sub-ranges starting at the LAST index of the
    # current window. This is because the last index of the current window was
    # not in the last window.
    if hi > 0:
        # If the range is longer than window K, count only the first K values.
        metric += (min(k, cache[1][hi]) - min(k, cache[3][hi]))

    cache[4][i] = metric
    return metric


def main():
    (N, K) = read(int)
    upvotes = read(int)

    cache = preprocess(upvotes)

    # Calculate metrics for the first K - 1 upvotes that do not constitute a
    # window of length K.
    for i in range(1, K - 1):
        metric_for_window(upvotes, cache, i, i + 1)

    # Calculate metrics for actual windows of length K.
    for i in range(K - 1, len(upvotes)):
        print(metric_for_window(upvotes, cache, i, K))

if __name__ == '__main__':
    main()
