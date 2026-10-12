#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
    struct Node {
        int child[2] = {-1, -1};
        int count = 0;
    };

    vector<Node> trie;

    void insertCode(int x, int delta) {
        int node = 0;
        trie[node].count += delta;

        for (int bit = 19; bit >= 0; --bit) {
            int b = (x >> bit) & 1;

            if (trie[node].child[b] == -1) {
                trie[node].child[b] = (int)trie.size();
                trie.emplace_back();
            }

            node = trie[node].child[b];
            trie[node].count += delta;
        }
    }

    int maxXor(int x) {
        int node = 0;
        int result = 0;

        for (int bit = 19; bit >= 0; --bit) {
            int b = (x >> bit) & 1;
            int opposite = b ^ 1;
            int next = trie[node].child[opposite];

            if (next != -1 && trie[next].count > 0) {
                result |= (1 << bit);
                node = next;
            } else {
                node = trie[node].child[b];
            }
        }

        return result;
    }

public:
    void solve() {
        int n, K;
        cin >> n >> K;

        trie.emplace_back();

        unordered_map<string, int> codes;
        unordered_map<string, bool> active;
        priority_queue<int, vector<int>, greater<int>> topK;

        for (int i = 0; i < n; ++i) {
            string operation, name;
            cin >> operation >> name;

            if (operation == "REGISTER") {
                int code;
                cin >> code;
                codes[name] = code;
                active[name] = true;
                insertCode(code, 1);
            } 
            else if (operation == "RETIRE") {
                insertCode(codes[name], -1);
                active[name] = false;
            } 
            else if (operation == "PING") {
                if (trie[0].count <= 1) {
                    cout << -1 << '\n';
                } else {
                    int value = maxXor(codes[name]);
                    cout << value << '\n';

                    if (K > 0) {
                        topK.push(value);
                        if ((int)topK.size() > K) {
                            topK.pop();
                        }
                    }
                }
            }
        }

        if (topK.empty()) {
            cout << "NONE\n";
            return;
        }

        vector<int> answer;
        while (!topK.empty()) {
            answer.push_back(topK.top());
            topK.pop();
        }

        reverse(answer.begin(), answer.end());

        for (int i = 0; i < (int)answer.size(); ++i) {
            if (i > 0) cout << ' ';
            cout << answer[i];
        }
        cout << '\n';
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution solution;
    solution.solve();

    return 0;
}
