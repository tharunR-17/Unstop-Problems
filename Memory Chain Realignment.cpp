#include <bits/stdc++.h>
using namespace std;

struct Node {
    int value;
    int pos;
    shared_ptr<Node> next;

    Node(int v, int p) : value(v), pos(p), next(nullptr) {}
};

int calculate_sum_of_first_k(shared_ptr<Node> head, int k) {
    queue<shared_ptr<Node>> q;
    q.push(head);
    int ans=0;
    while(!q.empty()){
        shared_ptr<Node> temp = q.front();
        q.pop();
        int value = temp->value;
        int pos = temp->pos;
        if(pos<=k) ans+=value;
        if(temp->next)         q.push(temp->next);
    }

    return ans; // Placeholder return
}

int main() {
    int n, k;
    cin >> n >> k;

    shared_ptr<Node> head = nullptr;
    shared_ptr<Node> tail = nullptr;

    for (int i = 0; i < n; ++i) {
        int v, p;
        cin >> v >> p;

        shared_ptr<Node> node = make_shared<Node>(v, p);
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    int result = calculate_sum_of_first_k(head, k);
    cout << result << endl;

    return 0;
}
