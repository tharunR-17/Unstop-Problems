#include <iostream>
#include <vector>
#include <utility>

using namespace std;

void dfs(int node, vector<int>&vis, vector<int>&pathvis, vector<int>&adjLs, 
vector<int>&path, int&ans){
    vis[node]=1;
    pathvis[node]=1;
    path.push_back(node);

    int edge=adjLs[node];
    if (edge!=-1){
        if (vis[edge]==0){
            dfs(edge, vis, pathvis, adjLs, path, ans);
        }
        else if (pathvis[edge]==1){
            int sum=0;
            for (int i=path.size()-1;i>=0; i--){
                sum++;
                if (path[i] == edge) break;
            }
            ans=max(ans, sum);
        }
    }
    pathvis[node]=0;
    path.pop_back();
}

// Placeholder function for user logic
int largest_scc(int N, const vector<pair<int, int>>& edges) {
    vector<int>adjLs(N+1, -1);
    for (auto it: edges){
        int from=it.first;
        int to=it.second;
        adjLs[from]=to;
    }
    vector<int>vis(N+1, 0);
    vector<int>pathvis(N+1, 0);
    int ans=0;
    for (int i=1;i<=N;i++){
        if (vis[i]==0){
            vector<int>path;
            dfs(i,vis, pathvis, adjLs, path, ans);
        }
    }
    
    return max(ans, 1); // Placeholder return
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    cin >> N >> M;
    
    vector<pair<int, int>> edges(M);
    for (int i = 0; i < M; ++i) {
        int A, B;
        cin >> A >> B;
        edges[i] = make_pair(A, B);
    }
    
    // Call the user logic function and print the result
    int result = largest_scc(N, edges);
    cout << result << endl;
    
    return 0;
}
