#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to get all smileys in sequence from the input string
vector<string> extract_smileys(const string& s) {
    vector<string> smileys;
    for (size_t i = 0; i + 1 < s.size(); ++i) {
        if (s[i] == ':' && (s[i+1] == ')' || s[i+1] == '(')) {
            smileys.push_back(s.substr(i, 2));
            i++; // Skip next character as it's part of smiley
        }
    }
    return smileys;
}

// User logic function
int user_logic(const string& s) {
    vector<string> smileys = extract_smileys(s);
    int pairs = 0;

    vector<string> stack;

    for (const string& smiley : smileys) {
        if (!stack.empty()) {
            string last = stack.back();
            if ((last == ":)" && smiley == ":(") || (last == ":(" && smiley == ":)")) {
                stack.pop_back();
                pairs++;
                continue;
            }
        }
        stack.push_back(smiley);
    }

    return pairs * 2; // Total number of smileys used in pairs
}


int main() {
    string s;
    getline(cin, s); // Read the entire line as input

    // Call user logic function and print the output
    int result = user_logic(s);
    cout << result << endl;

    return 0;
}
