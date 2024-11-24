# DSA_Project3
Project 3 for UF's COP 3530: Data Structures and Algorithms

# Project Details:
- Title: Whatever name Abdullah came up with last time (I forgot)
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
- If there are no words in the intersection, the program terminates; if there is only 1 word that is the predicted word, and if there is more than 1 the algorithm chooses the word with the highest probability to replace "MASK"

**Implementation:**
- Since for this project we have to use at least 2 non-trivial structures, we will be using both an edge list and an adjacency matrix to represent the graph.

**Team Roles:**
- Awwab will write the Python code to parse the dataset and generate the probabilities, as well as the `main` function.
- Abdullah will implement the Adjacency List and help with the video.
- Ahsan will do the edge list.
- We will collaborate together on the report.
