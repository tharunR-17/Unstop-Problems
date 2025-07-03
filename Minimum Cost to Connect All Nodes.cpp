#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Road {
    int from, to, cost;
};

bool cmpCost(const Road &a, const Road &b) {
    return a.cost < b.cost;
}

class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.assign(n, 1);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int get(int x) {
        return (parent[x] == x) ? x : (parent[x] = get(parent[x]));
    }

    bool join(int x, int y) {
        int px = get(x), py = get(y);
        if (px == py) return false;
        if (rank[px] < rank[py]) swap(px, py);
        parent[py] = px;
        if (rank[px] == rank[py]) rank[px]++;
        return true;
    }
};

int findMSTCost(int nodes, int edgesCount, vector<Road> &roads) {
    sort(roads.begin(), roads.end(), cmpCost);
    DSU dsu(nodes);
    int cost = 0, used = 0;
    for (auto &road : roads) {
        if (dsu.join(road.from, road.to)) {
            cost += road.cost;
            used++;
            if (used == nodes - 1) return cost;
        }
    }
    return -1;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Road> roads(m);
    for (int i = 0; i < m; ++i) {
        cin >> roads[i].from >> roads[i].to >> roads[i].cost;
    }
    cout << findMSTCost(n, m, roads) << '\n';
    return 0;
}
