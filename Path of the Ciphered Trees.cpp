#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    int id;
    char ch;
    int parent;
    vector<int> children;

    Node(int id, char ch, int parent) : id(id), ch(ch), parent(parent) {}
};

// Check if str has a palindrome of length >= 3
bool hasPalindrome(const string &str) {
    int n = str.size();
    for (int i = 0; i < n; ++i) {
        // Odd length palindrome
        int l = i, r = i;
        while (l >= 0 && r < n && str[l] == str[r]) {
            if (r - l + 1 >= 3) return true;
            --l; ++r;
        }
        // Even length palindrome
        l = i; r = i + 1;
        while (l >= 0 && r < n && str[l] == str[r]) {
            if (r - l + 1 >= 3) return true;
            --l; ++r;
        }
    }
    return false;
}

// Check if pathStr is a subsequence of S
bool isSubsequence(const string &pathStr, const string &S) {
    int j = 0;
    for (int i = 0; i < S.size() && j < pathStr.size(); ++i) {
        if (S[i] == pathStr[j]) j++;
    }
    return j == pathStr.size();
}

int user_logic(unordered_map<int, Node*>& nodes, const string& S) {
    unordered_set<int> isNotLeaf;
    for (auto &kv : nodes) {
        for (int child : kv.second->children) {
            isNotLeaf.insert(kv.first);
        }
    }

    vector<int> leaves;
    for (auto &kv : nodes) {
        if (isNotLeaf.find(kv.first) == isNotLeaf.end()) {
            leaves.push_back(kv.first);
        }
    }

    int result = 0;

    for (int leaf : leaves) {
        string pathStr;
        int node = leaf;
        while (node != -1) {
            pathStr += nodes[node]->ch;
            node = nodes[node]->parent;
        }

        string reversedPath = pathStr;
        reverse(reversedPath.begin(), reversedPath.end());

        if (isSubsequence(reversedPath, S) && hasPalindrome(pathStr)) {
            result++;
        }
    }

    return result;
}

int main() {
    int n;
    cin >> n;
    
    unordered_map<int, Node*> nodes;
    
    for (int i = 0; i < n; ++i) {
        int id, parent;
        char ch;
        cin >> id >> ch >> parent;
        
        nodes[id] = new Node(id, ch, parent);
        if (parent != -1) {
            nodes[parent]->children.push_back(id);
        }
    }
    
    string S;
    cin >> S;  // Last line is the cipher string
    
    int result = user_logic(nodes, S);
    cout << result << endl;
    
    for (auto& kv : nodes) {
        delete kv.second;
    }
    return 0;
}
