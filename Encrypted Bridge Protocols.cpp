#include <iostream>
#include <vector>
#include <unordered_set>
#include <utility>    // for std::pair
#include <string>

using namespace std;

const int MAX_LEN = 30; // max combined string length to explore

int N, M;
vector<vector<pair<int, string>>> graph;
unordered_set<string> allRotations;
bool found = false;

bool isPalindrome(const string& s) {
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        if (s[l++] != s[r--]) return false;
    }
    return true;
}

void generateRotations(const string& s, unordered_set<string>& rotSet) {
    string doubled = s + s;
    int len = (int)s.size();
    for (int i = 0; i < len; ++i) {
        rotSet.insert(doubled.substr(i, len));
    }
}

void dfs(int start,
         int current,
         const string& path,
         int depth,
         unordered_set<int>& uniqueNodes)
{
    if (found) return;
    if (depth > MAX_LEN) return;

    if (current == start && uniqueNodes.size() >= 3) {
        if (isPalindrome(path) && allRotations.count(path)) {
            found = true;
        }
        return;
    }

    for (const pair<int, string>& edge : graph[current]) {
        int nei = edge.first;
        const string& code = edge.second;

        // don't revisit intermediate nodes except to return to start
        if (uniqueNodes.count(nei) && nei != start) 
            continue;

        int newDepth = depth + (int)code.size();
        if (newDepth > MAX_LEN) 
            continue;

        bool newlyAdded = uniqueNodes.insert(nei).second;
        dfs(start,
            nei,
            path + code,
            newDepth,
            uniqueNodes);
        if (newlyAdded) {
            uniqueNodes.erase(nei);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    graph.assign(N + 1, vector<pair<int, string>>());

    vector<string> bridgeCodes;
    bridgeCodes.reserve(M);

    for (int i = 0; i < M; ++i) {
        int u, v;
        string s;
        cin >> u >> v >> s;
        graph[u].emplace_back(v, s);
        bridgeCodes.push_back(s);
    }

    // Precompute all possible rotations of each bridge code
    for (const string& code : bridgeCodes) {
        generateRotations(code, allRotations);
    }

    // Run DFS from every node
    for (int i = 1; i <= N && !found; ++i) {
        unordered_set<int> uniqueNodes;
        uniqueNodes.insert(i);
        dfs(i, i, string(), 0, uniqueNodes);
    }

    cout << (found ? "YES\n" : "NO\n");
    return 0;
}
