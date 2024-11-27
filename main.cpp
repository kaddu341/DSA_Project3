//
// Created by Awwab Ali Azam on 11/25/24.
//

# include <iostream>
# include <vector>
# include <fstream>
# include <sstream>
# include <filesystem>

using namespace std;

// declare helper function to process data
vector<tuple<string, string, float>> parseDataset(const string& wordsFile, const string& bigramsFile);

// main function
int main() {
  vector<tuple<string, string, float>> edges = parseDataset("data_processing/eng-simple_wikipedia_2021_300K/eng-simple_wikipedia_2021_300K-words.txt", "data_processing/eng-simple_wikipedia_2021_300K/eng-simple_wikipedia_2021_300K-co_n.txt");

  // testing
  const tuple<string, string, float>& test = edges.at(79);
  cout << get<0>(test) << endl;
  cout << get<1>(test) << endl;
  cout << get<2>(test) << endl;

  return 0;
}

// define the helper function
vector<tuple<string, string, float>> parseDataset(const string& wordsFile, const string& bigramsFile) {
  string cwd = filesystem::current_path().string();
  cwd = cwd.substr(0, cwd.find_last_of('/'));

  // get all the words and their indices and store them in an unordered map
  unordered_map<int, string> wordsMap;
  ifstream wordStream(cwd + "/" + wordsFile);
  string line;

  while (getline(wordStream, line)) {

    // break up each line into words
    istringstream iss(line);
    vector<string> entries;
    string entry;
    while (iss >> entry) {
      entries.push_back(entry);
    }

    // exception handling to avoid mis-processing data
    if (entries.size() == 3) {
      wordsMap[stoi(entries[0])] = entries[1];
    }
  }
  wordStream.close();

  // now process all the bigrams and store them in the return vector
  vector<tuple<string, string, float>> edges;
  ifstream bigramStream(cwd + "/" + bigramsFile);
  while (getline(bigramStream, line)) {

    // break up each line into words
    istringstream iss(line);
    vector<string> entries;
    string entry;
    while (iss >> entry) {
      entries.push_back(entry);
    }

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