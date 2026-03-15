#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> layer(n);
    for (int i = 0; i < n; i++)
        cin >> layer[i];

    int e;
    cin >> e;

    // edges not needed because patterns already valid
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
    }

    int p, maxSelect;
    cin >> p >> maxSelect;

    int layerCost;
    cin >> layerCost;

    vector<bitset<305>> nodeMask(p);
    vector<bitset<55>> layerMask(p);
    vector<int> importance(p);

    for (int i = 0; i < p; i++) {
        int m;
        cin >> m;

        for (int j = 0; j < m; j++) {
            int node;
            cin >> node;

            nodeMask[i].set(node);
            layerMask[i].set(layer[node]);
        }

        cin >> importance[i];
    }

    int ans = 0;

    int total = 1 << p;

    for (int mask = 1; mask < total; mask++) {

        if (__builtin_popcount(mask) > maxSelect)
            continue;

        bitset<305> usedNodes;
        bitset<55> usedLayers;

        int score = 0;
        bool ok = true;

        for (int i = 0; i < p; i++) {

            if (!(mask & (1 << i)))
                continue;

            if ((usedNodes & nodeMask[i]).any()) {
                ok = false;
                break;
            }

            usedNodes |= nodeMask[i];
            usedLayers |= layerMask[i];

            score += importance[i];
        }

        if (!ok)
            continue;

        int layerCount = usedLayers.count();

        int net = score - layerCount * layerCost;

        ans = max(ans, net);
    }

    cout << max(0, ans);

    return 0;
}
