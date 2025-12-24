#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int LG = 20;
const long long INF = 1e18;

struct Conn {
    int to, wt;
};

int nodes, queries;
vector<Conn> graph[N];
int up[N][LG], minWt[N][LG];
long long val[N];
int level[N];

void preprocess(int curr, int prev, long long wt) {
    up[curr][0] = prev;
    minWt[curr][0] = wt;
    for (int i = 1; i < LG; i++) {
        if (up[curr][i - 1] != -1) {
            up[curr][i] = up[up[curr][i - 1]][i - 1];
            minWt[curr][i] = min(minWt[curr][i - 1], minWt[up[curr][i - 1]][i - 1]);
        }
    }
    for (auto &e : graph[curr]) {
        int next = e.to, weight = e.wt;
        if (next == prev) continue;
        level[next] = level[curr] + 1;
        preprocess(next, curr, weight);
    }
}

int getLCA(int a, int b, int &minVal) {
    if (level[a] < level[b]) swap(a, b);
    minVal = INT_MAX;

    for (int i = LG - 1; i >= 0; i--) {
        if (up[a][i] != -1 && level[up[a][i]] >= level[b]) {
            minVal = min(minVal, minWt[a][i]);
            a = up[a][i];
        }
    }
    if (a == b) return a;

    for (int i = LG - 1; i >= 0; i--) {
        if (up[a][i] != up[b][i]) {
            minVal = min({minVal, minWt[a][i], minWt[b][i]});
            a = up[a][i];
            b = up[b][i];
        }
    }
    minVal = min({minVal, minWt[a][0], minWt[b][0]});
    return up[a][0];
}

long long pathSum(int a, int b) {
    int minCost;
    int lca = getLCA(a, b, minCost);
    long long total = 0;

    auto accumulate = [&](int x) {
        while (x != lca) {
            total += val[x] * minCost;
            x = up[x][0];
        }
    };

    accumulate(a);
    accumulate(b);
    total += val[lca] * minCost;
    return total;
}

void modifyEdge(int a, int b, int newWt) {
    for (auto &e : graph[a]) {
        if (e.to == b) {
            e.wt = newWt;
            break;
        }
    }
    for (auto &e : graph[b]) {
        if (e.to == a) {
            e.wt = newWt;
            break;
        }
    }
    memset(up, -1, sizeof(up));
    preprocess(1, -1, INF);
}

void run() {
    cin >> nodes >> queries;

    for (int i = 1; i <= nodes; i++) {
        cin >> val[i];
    }

    for (int i = 1; i < nodes; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    memset(up, -1, sizeof(up));
    preprocess(1, -1, INF);

    while (queries--) {
        int op;
        cin >> op;
        if (op == 1) {
            int idx, newVal;
            cin >> idx >> newVal;
            val[idx] = newVal;
        } 
        else if (op == 2) {
            int u, v, w;
            cin >> u >> v >> w;
            modifyEdge(u, v, w);
        } 
        else if (op == 3) {
            int u, v;
            cin >> u >> v;
            cout << pathSum(u, v) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    run();
    return 0;
}
