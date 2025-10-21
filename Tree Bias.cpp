#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1e5 + 5;

vector<int> adj[MAXN];
int depth[MAXN];
int bias = 0;

void dfs(int node, int parent, int d) {
    depth[node] = d;
    bias += d;
    for (int i = 0; i < adj[node].size(); i++) {
        int next = adj[node][i];
        if (next != parent) {
            dfs(next, node, d + 1);
        }
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, -1, 0);
    cout << bias << endl;
    return 0;
}
