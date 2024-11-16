#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Function to load the dictionary
void loadDictionary(const string& filename, unordered_set<string>& dictionary) {
    ifstream file(filename);
    string word;
    while (file >> word) {
        dictionary.insert(word);
    }
}

// Function to generate neighbors by changing one letter
vector<string> generateNeighbors(const string& word, const unordered_set<string>& dictionary) {
    vector<string> neighbors;
    for (size_t i = 0; i < word.length(); ++i) {
        string temp = word;
        for (char c = 'a'; c <= 'z'; ++c) {
            temp[i] = c;
            if (temp != word && dictionary.find(temp) != dictionary.end()) {
                neighbors.push_back(temp);
            }
        }
    }
    return neighbors;
}

// BFS to find the shortest word ladder
vector<string> findWordLadder(const string& start, const string& end, const unordered_set<string>& dictionary) {
    if (start == end) return {start};

    unordered_set<string> visited;
    queue<vector<string>> q;
    q.push({start});
    visited.insert(start);

    while (!q.empty()) {
        vector<string> path = q.front();
        q.pop();
        string currentWord = path.back();

        for (const string& neighbor : generateNeighbors(currentWord, dictionary)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                vector<string> newPath = path;
                newPath.push_back(neighbor);
                if (neighbor == end) return newPath;
                q.push(newPath);
            }
        }
    }
    return {};
}

// Main function
int main() {
    unordered_set<string> dictionary;
    loadDictionary("wordLadder_dictionary.txt", dictionary);

    string start, end;
    while (true) {
        cout << "Enter start word: ";
        cin >> start;
        cout << "Enter end word: ";
        cin >> end;
        
        vector<string> ladder = findWordLadder(start, end, dictionary);
        if (!ladder.empty()) {
            for (const string& word : ladder) {
                cout << word << " => ";
            }
            cout << "done" << endl;
        } else {
            cout << "No ladder exists" << endl;
        }
    }

    return 0;
}