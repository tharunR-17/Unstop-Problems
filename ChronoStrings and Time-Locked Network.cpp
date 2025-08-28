#include<bits/stdc++.h>
using namespace std;

void chronoShortestPath(int n, std::vector<std::string>& S, std::vector<std::vector<std::pair<int, int>>>& adj, int start, int end) {
    // Write your logic here.
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    vector<int> val(n+1, 0);
    int i = 1;

    auto calc = [&](string &s){
        int res = 0;

        for(char ch : s){
            res += (ch-'a'+1);
        }

        return res;
    };

    for(string &s : S){
        val[i++] = calc(s);
    }

    int ans = -1;

    vector<int> reachCost(n+1, -1);

    pq.push({val[start], start});
    reachCost[start] = val[start];



    while(!pq.empty())
    {
        auto nodeInfo = pq.top();
        pq.pop();

        int cost = nodeInfo.first;
        int node = nodeInfo.second;

        // cout<<node<<" "<<cost<<"\n";

        if(node==end){
            ans = cost;
            break;
        }

        for(auto it : adj[node]){
            int totCost = cost + it.second + val[it.first];
            if(reachCost[it.first] !=-1 && reachCost[it.first]<=totCost)continue;
            pq.push({totCost , it.first});
            reachCost[it.first]=totCost;
        }
    }

    cout<<ans<<"\n";


}

int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<std::string> S(N);
    for (int i = 0; i < N; i++) {
        std::cin >> S[i];
    }

    std::vector<std::vector<std::pair<int, int>>> adj(N + 1);
    for (int i = 0; i < M; i++) {
        int u, v, T;
        std::cin >> u >> v >> T;
        adj[u].emplace_back(v, T);
        adj[v].emplace_back(u, T);
    }

    int start, end;
    std::cin >> start >> end;

    chronoShortestPath(N, S, adj, start, end);

    return 0;
}
