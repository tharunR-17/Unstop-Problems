#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_NODES = 1e5 + 5;
vector<int> graph[MAX_NODES];
vector<int> groupMembers[MAX_NODES];
bool isInactive[MAX_NODES];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int nodes, groups, edges;
    cin >> nodes >> groups >> edges;

    vector<int> groupId(nodes);
    for (int i = 0; i < nodes; ++i) {
        cin >> groupId[i];
        --groupId[i];
        groupMembers[groupId[i]].push_back(i);
    }

    for (int i = 0; i < edges; ++i) {
        int from, to;
        cin >> from >> to;
        --from;
        --to;
        graph[from].push_back(to);
    }

    int queries;
    cin >> queries;
    while (queries--) {
        int start;
        cin >> start;
        --start;

        queue<int> bfsQueue;
        int affected = 0;

        for (int member : groupMembers[groupId[start]]) {
            if (!isInactive[member]) {
                isInactive[member] = true;
                ++affected;
                bfsQueue.push(member);
            }
        }

        while (!bfsQueue.empty()) {
            int current = bfsQueue.front();
            bfsQueue.pop();

            for (int neighbor : graph[current]) {
                if (!isInactive[neighbor]) {
                    for (int member : groupMembers[groupId[neighbor]]) {
                        if (!isInactive[member]) {
                            isInactive[member] = true;
                            ++affected;
                            bfsQueue.push(member);
                        }
                    }
                }
            }
        }

        cout << affected << '\n';
    }

    return 0;
}
