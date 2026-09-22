#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

class BinaryTrie {
    struct Node {
        int child[2];
        set<int> ids;  // station IDs ending at this exact code

        Node() {
            child[0] = child[1] = -1;
        }
    };

    vector<Node> trie;

public:
    BinaryTrie() {
        trie.emplace_back(); // root
    }

    void insert(int code, int id) {
        int node = 0;

        for (int bit = 19; bit >= 0; bit--) {
            int b = (code >> bit) & 1;

            if (trie[node].child[b] == -1) {
                trie[node].child[b] = trie.size();
                trie.emplace_back();
            }

            node = trie[node].child[b];
        }

        trie[node].ids.insert(id);
    }

    void erase(int code, int id) {
        int node = 0;
        vector<pair<int, int>> path;

        for (int bit = 19; bit >= 0; bit--) {
            int b = (code >> bit) & 1;
            path.push_back({node, b});
            node = trie[node].child[b];
        }

        trie[node].ids.erase(id);

        // Remove useless nodes from bottom to top.
        for (int i = 19; i >= 0; i--) {
            int parent = path[i].first;
            int b = path[i].second;
            int child = trie[parent].child[b];

            if (trie[child].ids.empty() &&
                trie[child].child[0] == -1 &&
                trie[child].child[1] == -1) {

                trie[parent].child[b] = -1;
            } else {
                break;
            }
        }
    }

    pair<int, int> query(int x) {
        int node = 0;
        int value = 0;

        // Maximize XOR greedily.
        for (int bit = 19; bit >= 0; bit--) {
            int b = (x >> bit) & 1;
            int opposite = b ^ 1;

            if (trie[node].child[opposite] != -1) {
                value |= (1 << bit);
                node = trie[node].child[opposite];
            } else {
                node = trie[node].child[b];
            }
        }

        // ids contains all active stations having this exact code.
        int bestId = *trie[node].ids.begin();

        return {value, bestId};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    BinaryTrie trie;

    // Current code of every active station.
    vector<int> codeOf(200001, -1);

    while (M--) {
        string operation;
        cin >> operation;

        if (operation == "ON") {
            int id, code;
            cin >> id >> code;

            codeOf[id] = code;
            trie.insert(code, id);
        }
        else if (operation == "OFF") {
            int id;
            cin >> id;

            trie.erase(codeOf[id], id);
            codeOf[id] = -1;
        }
        else if (operation == "CHECK") {
            int code;
            cin >> code;

            auto [maximumXor, stationId] = trie.query(code);

            cout << maximumXor << ' ' << stationId << '\n';
        }
    }

    return 0;
}
                
