# README

This is my solution to Quora's [Upvotes](https://www.hackerrank.com/contests/quora-haqathon/challenges/upvotes)
programming challenges.

This editorial uses variables from the original problem statement.

## Naive Solution

The naive solution is to calculate the metric separately for each window. This
can be done by counting the number of non-decreasing and non-increasing ranges
in each window [i, i + K - 1] in linear time.

The overall algorithm is O(N * K) which does not scale well for larger K's.

## Optimal Structure

We can use overlapping structure between adjacent windows to avoid
rediscovering shared ranges.

Say we have window W of length K starting at index i. The range of indeces this
window covers is [i, i + K - 1]. The previous window W' covers indeces
[i - 1, i + K - 2]. The overlap amongst W' and W is indeces [i, i + K - 2].

Given the metric for W' how can we compute the metric for W' in O(1) time?

Metric(W) = Metric(W') - (Ranges in W' starting at i - 1) + (Ranges in W ending at i + K - 2)

The question becomes, given an index i how can we efficiently calculate the
ranges in a window starting/ending at that index?

We can pre-calculate the distance from each index to the start/end of the
non-decreasing/increasing ranges it is part of in O(N) time. This information
can be accessed in O(1) time to calculate Metric(W) given Metric(W').

The code for this can be found in the `ranges` function of the solution code.

Several edge cases have not been discussed. Most importantly...

1. Handling the first K - 1 values that end windows with length less than K.
2. Handling cases where a distance from an index to the start/end of the
non-decreasing/increasing range it is part of is larger than K.

These edge cases are clear noted in the solution code if you are curious to
see how they are handled.

