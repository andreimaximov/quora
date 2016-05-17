# Quora Typeahead Search Challenge

This is my solution to the
[Quora Typeahead Search Challenge](https://www.quora.com/challenges#typeahead_search).

The challenge is also available on [HackerRank](https://www.hackerrank.com/contests/cs-quora/challenges/quora-typeahead-search).

## Final Algorithm

My solution uses a [TST](https://en.wikipedia.org/wiki/Ternary_search_tree) to
map each token to a set of items containing the token as a prefix. During an
insertion, item pointers are added to a set in each node along the path from the
root to the terminal node of the token/key.

During a query, the idea is to choose the token with the smallest item set and
perform a set intersection with the sets corresponding to the remaining query
tokens.

This is not space optimal because each node in the TST maintains a set of items
containing the prefix but has the highest performance to pass all test cases
without timing out.

## First Algorithm

My first solution was much more space efficient by storing item pointers only in
the **terminal** TST nodes. This allowed traversing down to the terminal node of
an arbitrary token in the query and then performing an exhaustive search in the
sub-trie for the top K items containing the remaining tokens as prefixes.

However, this resulted in a timeout for one of the test cases. I debated
guiding the search with a priority queue by keeping track of the maximum score
in each sub-trie but I didn't think this would be worth it because the
algorithm would need to check if each item in the sub-trie contained the
remaining query tokens as a prefix.

The algorithm would degrade quickly for cases where valid items that contained
all necessary tokens as prefixes had low scores and would thus be processed very
late by the priority queue guided traversal. However, I haven't verified real
world performance of this algorithm due to the complexity of the implementation
vs. my final solution.
