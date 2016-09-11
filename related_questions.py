#!/usr/bin/env python

import sys


class Question(object):
    def __init__(self, identifier, read_time):
        self._identifier = identifier
        self._read_time = read_time
        self._related = []
        self._graph_read_time= -1

    def identifier(self):
        return self._identifier

    def read_time(self):
        return self._read_time

    def get_related(self):
        return self._related

    def add_related(self, question):
        self._related.append(question)

    def get_graph_read_time(self):
        return self._graph_read_time

    def set_graph_read_time(self, read_time):
        self._graph_read_time = float(read_time)

    def __repr__(self):
        return self.__str__()

    def __str__(self):
        return 'Question (time = %d)' % self._time


def read(fn):
        return [fn(x) for x in sys.stdin.readline().split()]


def build_graph(N, T):
    graph = [Question(i, T[i]) for i in range(0, N)]

    for i in range(0, N - 1):
        (A, B) = read(int)
        A -= 1
        B -= 1
        graph[A].add_related(graph[B])
        graph[B].add_related(graph[A])

    return graph


def read_time(source, parent):
    assert source is not None

    time = source.read_time()

    children = source.get_related()

    n = len(children)
    if parent is not None:
        n -= 1

    for other in children:
        if other is parent:
            continue
        time += float(read_time(other, source)) / n

    source.set_graph_read_time(time)
    return time


def gather(source, parent, times):
    assert source is not None

    time = source.get_graph_read_time()

    if parent is not None:
        print('==========')

        parent_children = len(parent.get_related())

        parent_time = parent.get_graph_read_time()
        parent_time -= parent.read_time() + time / parent_children
        print(parent_time)
        if parent_children > 1:
            parent_time *= float(parent_children) / (parent_children - 1)
        print(parent_time)
        parent_time += parent.read_time()
        print(parent_time)

        print('Parent time went from %f to %f' % (parent.get_graph_read_time(), parent_time))

        source_children = len(source.get_related()) - 1

        source_time = source.get_graph_read_time()
        source_time -= source.read_time()
        print(source_time)
        source_time *= float(source_children) / (source_children + 1)
        print(source_time)
        source_time += parent_time / (source_children + 1) + source.read_time()
        print(source_time)

        print('Source time went from %d to %f' % (source.get_graph_read_time(), source_time))

        time = source_time
        source.set_graph_read_time(time)

    times[source.identifier()] = time

    for other in source.get_related():
        if other is parent:
            continue
        gather(other, source, times)


def main():
    N = int(sys.stdin.readline())
    T = read(int)
    graph = build_graph(N, T)

    read_time(graph[0], None)
    times = [0] * N
    gather(graph[0], None, times)

    source = 0
    for i in range(1, N):
        if times[i] < times[source]:
            source = i

    print(source + 1)


if __name__ == '__main__':
    main()
