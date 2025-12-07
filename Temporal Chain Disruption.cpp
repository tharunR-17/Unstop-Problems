#include <iostream>
#include <vector>
using namespace std;
int ans ;

void dfs(int node , vector<int> &visit ,   vector<vector<int>> &graph){

    visit[node] = 1;

    for(int neigh : graph[node]){
        if(visit[neigh] == 1){
            ans++;
        }
        else if(visit[neigh] == 0){
            dfs(neigh , visit , graph);
        }
    }



    visit[node] = 2;
}
// Placeholder for user logic function
int minEdgeRemovalsForDAG(int N, int M, const vector<int>& T, const vector<int>& S, const vector<pair<int, int>>& edges) {
    vector<int>visit(N , 0);
    ans = 0;
    vector<vector<int>>graph(N);
    for(int i = 0 ; i < M ; i++){
        int u = edges[i].first;
        int v = edges[i].second;
        graph[u - 1].push_back(v - 1);
    }   

    for(int i = 0 ; i < N  ; i++){
        if(visit[i] == 0){
            dfs(i , visit , graph);
        }
    }

    return ans;
    //return 0; 
}
int main() {
    int N, M;
    cin >> N >> M;

    vector<int> T(N);
    vector<int> S(N);
    for (int i = 0; i < N; ++i) {
        cin >> T[i]; // Reading timestamps
    }
    for (int i = 0; i < N; ++i) {
        cin >> S[i]; // Reading packet sizes
    }

    vector<pair<int, int>> edges(M);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v}; // Reading edges
    }

    // Call user logic function and print the result
    int result = minEdgeRemovalsForDAG(N, M, T, S, edges);
    cout << result << endl;

    return 0;
}
