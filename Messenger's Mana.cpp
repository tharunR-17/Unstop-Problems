#include <iostream>
#include <vector>
#include <deque>
#include <limits>
using namespace std;

struct Node {
    int x, y, weight;
};

int solve(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int rows, cols;
    cin >> rows >> cols;
    vector<vector<char>> mat(rows, vector<char>(cols));
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cin >> mat[i][j];
        }
    }
    
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    char dir[4] = {'a', 'b', 'c', 'd'};
    
    const int INF = numeric_limits<int>::max();
    vector<vector<int>> minCost(rows, vector<int>(cols, INF));
    
    deque<Node> q;
    minCost[0][0] = 0;
    q.push_back({0, 0, 0});
    
    while(!q.empty()){
        Node curr = q.front();
        q.pop_front();
        int x = curr.x, y = curr.y, cost = curr.weight;
        if(cost > minCost[x][y])
            continue;
        for (int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx < 0 || nx >= rows || ny < 0 || ny >= cols)
                continue;
            int addCost = (mat[x][y] == dir[i] ? 0 : 1);
            int total = cost + addCost;
            if(total < minCost[nx][ny]){
                minCost[nx][ny] = total;
                if(addCost == 0)
                    q.push_front({nx, ny, total});
                else
                    q.push_back({nx, ny, total});
            }
        }
    }
    
    cout << minCost[rows-1][cols-1] << "\n";
    return 0;
}

int main() {
    return solve();
}
