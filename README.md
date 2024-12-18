# DSA_Project3
Project 3 for UF's COP 3530: Data Structures and Algorithms

# Instructions to Run Code
- Simply clone the repository into CLion and click the green "play" button in the top right corner to compile and run the C++ code (the CMakeLists.txt is included in the source).

# Project Details:
- Title: Deterministic Masked Language Modeler
- Description: A masked language modeling program using a bigram statistical machine learning model to predict words.

**Functionality:**
- *Input:* A string with exactly one "MASK" character
- Examples:
  1. "MASK" fat cat sat on the mat
  2. The fat "MASK" sat on the mat
  3. The fat cat sat on the "MASK"

- *Output:* A string identical to the input with the "MASK" character replaced by the predicted word.
- Examples:
  1. The fat cat sat on the mat

**Algorithm:**
- We have a dataset of 300k English sentences from Wikipedia (https://wortschatz.uni-leipzig.de/en/download/English)
- Using this dataset, we can calculate the frequencies of each word, thereby obtaining the bigram probabilities, which will be stored in a .txt file.
- The data will be in the form "first word" "second word" "probability"
- Example:
  ```
  The fat 0.01
  The cat 0.03
  The bat 0.01
  The rat 0.05
  sat on 0.02
  the mat 0.35
  etc.
  ```

- This data can be represented in the form of a graph, where an edge from Node A to Node B implies that B has some probability of coming after the word A and the weight of the edge is this probability.
- Example: if the probability of the bigram "sat on" is 0.02, that means there is an edge from "sat" to "on" with weight 0.02.

- When given a sentence, the algorithm finds the word before "MASK" and the word after "MASK" (if either don't exist, they will just be set to null).
- Then, it searches through the **outdegrees** of the first word and the **indegrees** of the second word and tries to find their intersection.
- If there are no words in both of these vectors, the program terminates; otherwise, we compute the intersection and (if it is nonempty) choose the word with the highest probability that occurs in both vectors. If the intersection is empty, then we simply choose the word with the highest probability overall to replace "MASK"

**Implementation:**
- Since for this project we have to use at least 2 non-trivial structures, we will be using both an edge list and an adjacency matrix to represent the graph.

**Team Roles:**
- Awwab will write the C++ code for parsing the dataset and the abstract `Graph` class, as well as the `main` function.
- Abdullah will implement the Adjacency List and help with the video.
- Ahsan will implement the edge list.
- We will collaborate together on the report.

**Structure:**
- main.cpp
  1. parsing dataset into a vector<tuple<string, string, float>> in the form (from, to, weight).
  2. manage I/O (implement algorithm)
- Graph ADT
  1. constructor(vector<tuple<string, string, float>>)
  2. vector<pair<string, float>> outdegrees(string word) in the form (to, weight)
  3. vector<pair<string, float>> outdegrees(string word) in the form (from, weight)
  4. destructor()
