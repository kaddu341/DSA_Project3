# pragma once

#include <unordered_map>
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

   // this should be overridden to return a vector of all the outdegrees of a given word and associated weights; should return empty vector if no outdegrees
   virtual vector<pair<string, float>> outdegrees(string word) = 0;

   // this should be overridden to return a vector of all the indegrees of a given word and associated weights; should return empty vector if no indegrees
   virtual vector<pair<string, float>> indegrees(string word) = 0;

   // virtual destructor
   virtual ~Graph() = default;
};


class AdjacencyList : public Graph {
private:
    // Adjacency list representation: node -> vector of (neighbor, weight)
    // adjacency list for outdegrees
    unordered_map<string, vector<pair<string, float>>> outDegreeList;
    // Reverse adjacency list for indegrees
    unordered_map<string, vector<pair<string, float>>> inDegreeList;

public:
    explicit AdjacencyList(const vector<tuple<string, string, float>>& edges)
            : Graph(edges) {
        for (const auto& edge : edges) {
            string from = get<0>(edge);
            string to = get<1>(edge);
            float weight = get<2>(edge);

            // makes outdegree vector
            outDegreeList[from].emplace_back(to, weight);

            // makes indegree vector
            inDegreeList[to].emplace_back(from, weight);
        }
    }

    vector<pair<string, float>> outdegrees(string word) override {
        if (outDegreeList.find(word) != outDegreeList.end()) {
            return outDegreeList[word];
        }
        return {}; // Return empty vector if no outdegrees
    }

    vector<pair<string, float>> indegrees(string word) override {
        if (inDegreeList.find(word) != inDegreeList.end()) {
            return inDegreeList[word];
        }
        return {}; // Return empty vector if no indegrees
    }

    ~AdjacencyList() override = default;
};

class EdgeList : public Graph {
private:
    // List of edges in the form (from, to, weight)
    vector<tuple<string, string, float>> edges;

public:
    explicit EdgeList(const vector<tuple<string, string, float>>& edges)
            : Graph(edges), edges(edges) {}

    vector<pair<string, float>> outdegrees(string word) override {
        vector<pair<string, float>> result;
        for (const auto& edge : edges) {
            if (get<0>(edge) == word) { // Check 'from' matches the word
                result.emplace_back(get<1>(edge), get<2>(edge));
            }
        }
        return result; // Return outdegrees
    }

    vector<pair<string, float>> indegrees(string word) override {
        vector<pair<string, float>> result;
        for (const auto& edge : edges) {
            if (get<1>(edge) == word) { // Check 'to' matches the word
                result.emplace_back(get<0>(edge), get<2>(edge));
            }
        }
        return result; // Return indegrees
    }

    ~EdgeList() override = default;
};


