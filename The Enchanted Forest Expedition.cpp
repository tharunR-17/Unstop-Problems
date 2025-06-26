#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100005;
vector<int> graph[MAXN];
int a[MAXN];
bool visited[MAXN];
int max_power = 0, farthest_node = 0;

void dfs(int node, int parent, int current_sum) {
    current_sum += a[node];
    if (current_sum > max_power) {
        max_power = current_sum;
        farthest_node = node;
    }

    for (int neighbor : graph[node]) {
        if (neighbor != parent) {
            dfs(neighbor, node, current_sum);
        }
    }
}

int main() {
    int n;
    cin >> n;
    
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }

    dfs(0, -1, 0); // First DFS to find farthest node
    max_power = 0;
    dfs(farthest_node, -1, 0); // Second DFS for max power

    cout << max_power << endl;
    return 0;
}
