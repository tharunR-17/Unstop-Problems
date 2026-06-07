#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

string specialmsg(string s, vector<vector<string>> vocab) {
    // Create a map to store key-value pairs
    unordered_map<string, string> vocabMap;
    for (const auto& pair : vocab) {
        vocabMap[pair[0]] = pair[1];
    }

    string result;
    size_t i = 0;
    while (i < s.length()) {
        // Check if we found an opening parenthesis
        if (s[i] == '(') {
            size_t j = i + 1;
            // Find the closing parenthesis
            while (j < s.length() && s[j] != ')') {
                j++;
            }
            // If we found a closing parenthesis
            if (j < s.length()) {
                // Extract the acronym
                string acronym = s.substr(i + 1, j - i - 1);
                // Replace with the corresponding value or "?"
                if (vocabMap.find(acronym) != vocabMap.end()) {
                    result += vocabMap[acronym];
                } else {
                    result += "?";
                }
                // Move the index past the closing parenthesis
                i = j + 1;
            } else {
                // If no closing parenthesis found, just append the rest of the string
                result += s.substr(i);
                break;
            }
        } else {
            // If not an acronym, just append the character
            result += s[i];
            i++;
        }
    }

    return result;
}

int main() {
    string s;
    getline(cin, s); // Use getline to read the entire line including spaces

    int size;
    cin >> size;
    cin.ignore(); // Ignore the newline after the integer input

    vector<vector<string>> vocab(size, vector<string>(2));
    for(int i = 0; i < size; i++) {
        cin >> vocab[i][0] >> vocab[i][1];
    }

    string ans = specialmsg(s, vocab);
    cout << ans;

    return 0;
}
