#include <iostream>
#include <vector>

using namespace std;

struct Thread {
    int u, v;
};

struct QueryInfo {
    int t, id;
};

// DSU structures
vector<int> parent;
vector<int> sz;

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b, vector<int>& count_size) {
    int ra = find_set(a);
    int rb = find_set(b);
    if (ra != rb) {
        if (sz[ra] < sz[rb])
            swap(ra, rb);
        // Decrement counts of the old individual component sizes
        count_size[sz[ra]]--;
        count_size[sz[rb]]--;
        
        // Merge
        parent[rb] = ra;
        sz[ra] += sz[rb];
        
        // Increment count of the new merged component size
        count_size[sz[ra]]++;
    }
}

int main() {
    // Optimize standard input/output streams for speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<Thread> threads(M + 1);
    for (int i = 1; i <= M; ++i) {
        cin >> threads[i].u >> threads[i].v;
    }

    int Q;
    if (!(cin >> Q)) return 0;

    // Group queries by their moment k
    vector<vector<QueryInfo>> queries_at(M + 1);
    for (int i = 0; i < Q; ++i) {
        int k, t;
        cin >> k >> t;
        queries_at[k].push_back({t, i});
    }

    // Initialize DSU
    parent.resize(N + 1);
    sz.resize(N + 1, 1);
    for (int i = 1; i <= N; ++i) {
        parent[i] = i;
    }

    // count_size[t] stores how many clusters have size t
    vector<int> count_size(N + 1, 0);
    count_size[1] = N; // Initially N separate lanterns of size 1

    vector<int> ans(Q);

    // Process moments from 0 to M
    for (int k = 0; k <= M; ++k) {
        // Answer all queries at moment k
        for (const auto& q : queries_at[k]) {
            if (q.t <= N) {
                ans[q.id] = count_size[q.t];
            } else {
                ans[q.id] = 0;
            }
        }

        // Apply thread k + 1 if available
        if (k < M) {
            union_sets(threads[k + 1].u, threads[k + 1].v, count_size);
        }
    }

    // Print all answers separated by spaces
    for (int i = 0; i < Q; ++i) {
        cout << ans[i] << (i == Q - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}
