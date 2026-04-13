#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int, int> State;

const ll INF = LLONG_MAX / 2;

int N, M, K;
vector<tuple<int,int,int>> adj[100005];
ll dist[100005][2][16];

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;

    vector<int> switch_cost(N);
    for (int i = 0; i < N; i++)
        cin >> switch_cost[i];

    for (int i = 0; i < M; i++) {
        int u, v, nl, ql;
        cin >> u >> v >> nl >> ql;
        adj[u].push_back({v, nl, ql});
        adj[v].push_back({u, nl, ql});
    }

    for (int i = 0; i < N; i++)
        for (int m = 0; m < 2; m++)
            for (int q = 0; q <= K; q++)
                dist[i][m][q] = INF;

    priority_queue<State, vector<State>, greater<State>> pq;

    dist[0][0][0] = 0;
    pq.push({0, 0, 0, 0});

    while (!pq.empty()) {
        auto [d, u, mode, qj] = pq.top(); pq.pop();

        if (d > dist[u][mode][qj]) continue;
        if (u == N - 1) {
            cout << d << "\n";
            return 0;
        }

        int new_mode = 1 - mode;
        ll nd = d + switch_cost[u];
        if (nd < dist[u][new_mode][0]) {
            dist[u][new_mode][0] = nd;
            pq.push({nd, u, new_mode, 0});
        }

        for (auto [v, nl, ql] : adj[u]) {
            if (mode == 0) {
                nd = d + nl;
                if (nd < dist[v][0][0]) {
                    dist[v][0][0] = nd;
                    pq.push({nd, v, 0, 0});
                }
            } else {
                if (qj < K) {
                    nd = d + ql;
                    int nqj = qj + 1;
                    if (nd < dist[v][1][nqj]) {
                        dist[v][1][nqj] = nd;
                        pq.push({nd, v, 1, nqj});
                    }
                }
            }
        }
    }

    ll ans = INF;
    for (int m = 0; m < 2; m++)
        for (int q = 0; q <= K; q++)
            ans = min(ans, dist[N-1][m][q]);

    cout << (ans == INF ? -1 : ans) << "\n";
    return 0;
}
