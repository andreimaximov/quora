# Quora Ontology Challenge

This is my solution to Quora's [Ontology](https://www.quora.com/challenges#ontology)
challenge.

## Build

I decided to learn a bit about [CMake](https://cmake.org) with this project.
Just go to the `build` directory and execute `cmake ..`. Of course you need to
install CMake for this to work.

This will generate a build pipeline for your system. On Mac/Linux this should
generate a `Makefile` so you can just run `make` in the `build` directory and
run the compiled `ontology` executable.

## Editorial

The main idea is that since the ontology is a tree, we can map each topic `t`
to a range `[lo, hi]` such that `lo(t) <= hi(t)`, `lo(parent(t)) <= lo(t)`,
and `hi(parent(t)) <= hi(t)` via a Euler Tour.

We can then construct a prefix trie of questions. For each query we find the
node in the trie representing the last character in the prefix. This reduces
our search space to the set of questions with the query prefix. We just need
to figure out how many questions `x` in this set there are such that
`topic(x).lo >= topic(query).lo` and `topic(x).hi <= topic(query).hi`.

We can accomplish this in `O(log M)` time if we keep some info in each node
about the topics of questions with the prefix ending at the node. This is
explained in [trie.hpp](include/trie.hpp) doc blocks.
