//
// Created by Awwab Ali Azam on 11/25/24.
//

# include <iostream>
# include <vector>
# include <fstream>
# include <sstream>
# include <unordered_map>
# include "Graph.h"
# include <algorithm>

using namespace std;

// declare helper functions to process data
vector<tuple<string, string, float>> parseDataset(const string& wordsFile, const string& bigramsFile);
vector<string> chunkify(const string& line);
bool comp(const pair<string, float>& a, const pair<string, float>& b);

// main function
int main() {
  Graph* graph;

  // welcome message
  cout << "Welcome to the Deterministic Masked Language Modeler!\n";

  cout << "Loading data...";
  // "../" for parent directory in relative path
  vector<tuple<string, string, float>> edges = parseDataset("../data_processing/eng-simple_wikipedia_2021_300K/eng-simple_wikipedia_2021_300K-words.txt", "../data_processing/eng-simple_wikipedia_2021_300K/eng-simple_wikipedia_2021_300K-co_n.txt");
  cout << "Done!\n";

  // process user input
  string choice;
  cout << "Which data structure would you like to use today? Options: [0 for adjacency list; 1 for edge list]\n";
  getline(cin, choice);

  if (choice == "0") {
    graph = new AdjacencyList(edges);
      cout << "Using Adjacency List\n";
  }
  else if (choice == "1") {
    graph = new EdgeList(edges);
      cout << "Using Edge List\n";
  }
  else {
    cout << "Sorry, Invalid Input\n";
    return 0;
  }

  // free memory in vector now that it is no longer needed; Credit: https://stackoverflow.com/questions/10464992/c-delete-vector-objects-free-memory
  vector<tuple<string, string, float>>().swap(edges);

  // run masked language modeling algorithm
  while (true) {
    // get the sentence
    string sentence;
    cout << "Please enter a sentence (q to quit):\n";
    getline(cin, sentence);

    // base case to quit
    if (sentence == "q") {
      break;
    }

    // break the sentence into words
    vector<string> words = chunkify(sentence);

    // get the "context words" before and after the [MASK] token
    string beforeWord;
    string afterWord;
    // search for the [MASK] token
    auto it = find(words.begin(), words.end(), "[MASK]");

    // exception handling
    if (it == words.end()) {
      cout << "Sorry, for masked language modeling the sentence must have a [MASK] token\n";
      continue;
    }
    unsigned int index = distance(words.begin(), it);
    if (index > 0) {
      beforeWord = words.at(index - 1);
    }
    if (index < words.size() - 1) {
      afterWord = words.at(index + 1);
    }

    // get the outdegree and indegree vectors of the "before" and "after" words, respectively
    vector<pair<string, float>> v1 = graph->outdegrees(beforeWord);
    vector<pair<string, float>> v2 = graph->indegrees(afterWord);

    // implement algorithm to choose the most likely candidate word
    string predictedWord;

    // first, sort both vectors in descending order
    sort(v1.begin(), v1.end(), comp);
    sort(v2.begin(), v2.end(), comp);

    // more exception handling
    if (v1.empty() && v2.empty()) {
      cout << "Sorry, the algorithm has gotten confused\n";
      continue;
    }
    if (v1.empty()) {
      predictedWord = v2.at(0).first;
    }
    else if (v2.empty()) {
      predictedWord = v1.at(0).first;
    }
    else {
      // find the word with the highest probability
      float probability = 0.0;
      for (const pair<string, float>& p : v1) {
        // check if the same word exists in v2
        for (const pair<string, float>& q : v2) {
          if (p.first == q.first) {
            float sum = p.second + q.second;
            if (sum > probability) {
              predictedWord = p.first;
              probability = sum;
            }
          }
        }
      }
      // in case there was no overlap
      if (predictedWord.empty()) {
        if (v1.at(0).second > v2.at(0).second) {
          predictedWord = v1.at(0).first;
        }
        else {
          predictedWord = v2.at(0).first;
        }
      }
    }

    // now that the predicted word has been found, replace it in the sentence and print out the result
    words[index] = predictedWord;
    string newSentence;
    for (const string& word : words) {
      newSentence += word + " ";
    }
    cout << "Predicted Sentence: " << newSentence << endl;
  }
  // Free memory
  delete graph;

  // Farewell message
  cout << "Thank you so much for using the Deterministic Masked Language Modeler today!\n";

  return 0;
}

// define the helper functions
vector<tuple<string, string, float>> parseDataset(const string& wordsFile, const string& bigramsFile) {

  // get all the words and their indices and store them in an unordered map
  unordered_map<int, string> wordsMap;
  ifstream wordStream(wordsFile);
  string line;

  while (getline(wordStream, line)) {

    // break up each line into words
    vector<string> entries = chunkify(line);

    // exception handling to avoid mis-processing data
    if (entries.size() == 3) {
      wordsMap[stoi(entries[0])] = entries[1];
    }
  }
  wordStream.close();

  // now process all the bigrams and store them in the return vector
  vector<tuple<string, string, float>> edges;
  ifstream bigramStream(bigramsFile);
  while (getline(bigramStream, line)) {

    // break up each line into words
    vector<string> entries = chunkify(line);

    // exception handling to avoid mis-processing data
    if (entries.size() == 4) {
      int index1 = stoi(entries[0]);
      int index2 = stoi(entries[1]);

      if ((wordsMap.find(index1) != wordsMap.end()) && (wordsMap.find(index2) != wordsMap.end())) {
        edges.emplace_back(wordsMap[stoi(entries[0])], wordsMap[stoi(entries[1])], stof(entries[3]));
      }
    }
  }
  bigramStream.close();

  // return the result
  return edges;
}

// function to break up a longer string into words
vector<string> chunkify(const string& line) {
  istringstream iss(line);
  vector<string> entries;
  string entry;
  while (iss >> entry) {
    entries.push_back(entry);
  }
  return entries;
}

// custom comparator for std::sort function
bool comp(const pair<string, float>& a, const pair<string, float>& b) {
  return a.second > b.second;
}
