#include <iostream>
#include <unordered_map>
using namespace std;

struct Node {
    int id, value;
    Node* next;
    bool visited;
    Node(int i, int v) : id(i), value(v), next(nullptr), visited(false) {}
};

void traverseAndPrint(Node* head) {
    Node* curr = head;
    while (curr) {
        if (curr->visited) break;
        cout << curr->value << " ";
        curr->visited = true;
        if (curr->next && curr->next->visited) {
            curr->next = nullptr;  // break cycle
        }
        curr = curr->next;
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;

    unordered_map<int, Node*> nodeMap;
    unordered_map<int, int> nextMap;

    for (int i = 0; i < n; ++i) {
        int nodeId, val, nextId;
        cin >> nodeId >> val >> nextId;
        nodeMap[nodeId] = new Node(nodeId, val);
        nextMap[nodeId] = nextId;
    }

    int startId;
    cin >> startId;

    // Reconstruct forward pointers
    for (auto& entry : nextMap) {
        int from = entry.first;
        int to = entry.second;
        if (to != -1)
            nodeMap[from]->next = nodeMap[to];
    }

    Node* start = nodeMap[startId];
    traverseAndPrint(start);

    return 0;
}
