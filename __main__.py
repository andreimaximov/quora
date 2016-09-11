#!/usr/bin/env python

import sys


def read(fn):
    return [fn(x) for x in sys.stdin.readline().split(' ')]


def main():
    (N, K) = read(int)
    upvotes = read(int)

if __name__ == "__main__":
    main()
