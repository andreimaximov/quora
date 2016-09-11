#!/usr/bin/env python

import sys


class Question(object):
    def __init__(self, time):
        self._time = time
        self._related = []

    def time(self):
        return self._time

    def related(self, question):
        self._related.append(question)

    def __repr__(self):
        return self.__str__()

    def __str__(self):
        return 'Question (time = %d)' % self._time


def read(fn):
        return [fn(x) for x in sys.stdin.readline().split()]


def build_graph(N, T):
    graph = [Question(T[i]) for i in range(0, N)]

    for i in range(0, N - 1):
        (A, B) = read(int)
        A -= 1
        B -= 1
        graph[A].related(B)
        graph[B].related(A)

    return graph


def main():
    N = int(sys.stdin.readline())
    T = read(int)
    graph = build_graph(N, T)
    print(graph)

if __name__ == '__main__':
    main()
