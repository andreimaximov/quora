#!/usr/bin/env python

import sys


def read(fn):
    return [fn(x) for x in sys.stdin.readline().split()]


def count_sub_ranges(n):
    assert n > 1
    return int((n ** 2 - n) / 2)


def count_ranges(upvotes, lo, hi, comparator):
    count = 0
    start = lo
    for i in range(lo, hi + 1):
        if i < hi and comparator(upvotes[i], upvotes[i + 1]):
            continue
        length = i - start + 1
        # Ensure that a < b for range [a, b]
        if length > 1:
            count += count_sub_ranges(length)
        start = i + 1

    return count


def non_decreasing(lhs, rhs):
    return lhs <= rhs


def non_increasing(lhs, rhs):
    return lhs >= rhs


def metric_for_window(upvotes, i, k):
    hi = i + k - 1
    nd_count = count_ranges(upvotes, i, hi, non_decreasing)
    ni_count = count_ranges(upvotes, i, hi, non_increasing)
    return nd_count - ni_count


def main():
    (N, K) = read(int)
    upvotes = read(int)

    for i in range(0, len(upvotes) - K + 1):
        print(metric_for_window(upvotes, i, K))

if __name__ == '__main__':
    main()
