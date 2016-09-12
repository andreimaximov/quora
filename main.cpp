#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using std::vector;

struct question {
  //
  // The time it takes to read just this question.
  //
  uint32_t read_time;

  //
  // Identifiers of related questions.
  //
  vector<size_t> related;

  //
  // The expected time it will take to exhaust related questions if a user
  // starts reading this question.
  //
  double tree_read_time;
};

//
// Builds a graph with n nodes and n - 1 edges as outlined by the problem
// statement.
//
vector<question> build_graph(uint32_t n) {
  vector<question> graph(n);

  for (size_t i = 0; i < n; i++) {
    std::cin >> graph[i].read_time;
  }

  for (size_t i = 0; i < n - 1; i++) {
    size_t a, b;
    std::cin >> a >> b;
    a--; b--;  // We are using a 0-index system.
    graph[a].related.push_back(b);
    graph[b].related.push_back(a);
  }

  return graph;
}

//
// Calculates the expected read time starting at the specified source question.
// The parent indicates the question that was processed in the last iteration
// and lead to the current source question. The parent should not be processed
// again.
//
double read_time(vector<question>& graph, size_t source, size_t parent) { // NOLINT
  double time = graph[source].read_time;

  size_t edges = graph[source].related.size();

  // If there was a parent that lead to this source, do not count it as a
  // candidate edge.
  if (source != parent) {
    edges--;
  }

  // Process children and factor in reading time as a weighted average of the
  // number of children.
  for (size_t other : graph[source].related) {
    // Ignore question that lead to this one and has already been processed.
    if (other == parent) {
      continue;
    }

    time += read_time(graph, other, source) / edges;
  }

  graph[source].tree_read_time = time;
  return time;
}

//
// Traverses the tree selecting each node as a root and calculating the
// expected reading time if a user started reading from that question. The tree
// must already have expected reading times calculated for all sub-trees of the
// tree rooted at the source question.
//
void traverse_roots(vector<question>& graph, // NOLINT
                    vector<double>& times, // NOLINT
                    size_t source,
                    size_t parent) {
  double time = graph[source].tree_read_time;

  // Flip the parent - child relationship between source and parent.
  if (source != parent) {
    size_t parent_children = graph[parent].related.size();
    double parent_time = graph[parent].tree_read_time;

    // Calculate how much all children of parent except for source contribute
    // to the reading time of parent.
    parent_time -= (graph[parent].read_time + time / parent_children);

    // Adjust the reading time because we are no longer considering the current
    // source question as a child of the parent question.
    if (parent_children > 1) {
      parent_time *= static_cast<double>(parent_children) /
        (parent_children - 1);
    }

    // Add back the time it takes to read just the parent to its expected
    // reading time.
    parent_time += graph[parent].read_time;

    // The number of children the current source question has since one of the
    // edges is the parent. This will increase by one as we make the parent a
    // child.
    size_t source_children = graph[source].related.size() - 1;

    double source_time = graph[source].tree_read_time;

    // This is now just the time that the childrne of the source question
    // contribute to its expected reading time. This does not include the
    // parent which will become a child yet.
    source_time -= graph[source].read_time;

    // Scale down how much the existing children contribute to reading time as
    // we add another child - the parent.
    source_time *= static_cast<double>(source_children) /
      (source_children + 1);

    // Factor in the weighted share of how much the parent, now a child,
    // contributes to the reading time of this question.
    source_time += parent_time /  (source_children + 1);

    // Don't forget to add back in the reading time of the question itself.
    source_time += graph[source].read_time;

    time = source_time;
    graph[source].tree_read_time = time;
  }

  times[source] = time;

  for (size_t other : graph[source].related) {
    // Ignore parent. We've already processed it!
    if (other == parent) {
      continue;
    }
    traverse_roots(graph, times, other, source);
  }
}

int main() {
  uint32_t N;
  std::cin >> N;
  vector<question> graph = build_graph(N);

  read_time(graph, 0, 0);
  vector<double> times(N);
  traverse_roots(graph, times, 0, 0);

  // Find the question with the shortest expected reading time.
  size_t source = 0;
  for (size_t i = 1; i < N; i++) {
    if (times[i] < times[source]) {
      source = i;
    }
  }

  std::cout << (source + 1) << std::endl;

  return 0;
}

