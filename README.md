# README

This is my solution to Quora's [Related Questions](https://www.hackerrank.com/contests/quora-haqathon/challenges/relatedquestions)
challenge.

# Terms

- <strong>ERT</strong> = Expected Reading Time

# Naive Solution

The naive solution is to separately consider each node as a root and
recursively calculate the ERT for each using a weighted average. Then just
select the node with the shortest reading time.

Unfortunately this is a `O(N^2)` algorithm which does not scale well for large
N.

# Optimal Solution

Instead of recalculating the ERT for each root we can first calculate
the expected reading time once for an arbitrary node S while keeping a cache of
ERT's for all sub-trees.

Once this `O(N)` preprocessing step is complete, we can recursively shift the
node form S to each of it's children.

For example, say we are shifting the root from question A to B. We can call
question A the parent and B the child. When doing this operation there are two
key points we have to note.

1. The `ERT(B)` is factored into `ERT(A)` as a weighted average.
2. A or any path through A was never factored into the `ERT(B)` since A is a
parent.

This means that when we are shifting the root from A to B we also need to make
A a child of B. This can be broken up into 2 main steps.

1. Un-factor `ERT(B)` from `ERT(A)`.
2. Factor the new `ERT(B)` into `ERT(A)`.

The code for both of these steps is fairly simple can can be found in the
`traverse_roots` function.

