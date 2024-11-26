# pragma once
# include <tuple>
# include <vector>
# include <string>

using namespace std;

// Abstract class to define an "interface" for the two graph implementations
// The EdgeList and AdjacencyList classes should inherit from this class
class Graph {
public:
   // base constructor: the child classes' constructors should initialize the graph data.
   // the elements of the edges vector are in the form (from, to, weight)
   explicit Graph(const vector<std::tuple<string, string, float>>& edges) {}

   // this should be overridden to return a vector of all the outdegrees of a given word and associated weights
   virtual vector<pair<string, float>> outdegrees(string word) = 0;

   // this should be overridden to return a vector of all the indegrees of a given word and associated weights
   virtual vector<pair<string, float>> indegrees() = 0;

   // virtual destructor
   virtual ~Graph() = default;
};
