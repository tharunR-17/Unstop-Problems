#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int val;
    Node* prev;
    Node* next;
    Node(int v) : val(v), prev(nullptr), next(nullptr) {}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    
    if (n == 0) return 0;
    
    Node* head = nullptr;
    Node* tail = nullptr;
    
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        Node* node = new Node(v);
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }
    
    Node* curr = head;
    Node* newHead = nullptr;
    Node* prevBlockTail = nullptr;
    bool shouldReverse = true;
    
    while (curr) {
        if (shouldReverse) {
            Node* blockStart = curr;
            Node* blockEnd = curr;
            int count = 1;
            
            while (count < k && blockEnd->next) {
                blockEnd = blockEnd->next;
                count++;
            }
            
            Node* nextBlockStart = blockEnd->next;
            
            Node* node = blockStart;
            while (node != nextBlockStart) {
                Node* tmp = node->next;
                node->next = node->prev;
                node->prev = tmp;
                node = tmp;
            }
            
            blockEnd->prev = prevBlockTail;
            blockStart->next = nextBlockStart;
            
            if (prevBlockTail) {
                prevBlockTail->next = blockEnd;
            } else {
                newHead = blockEnd;
            }
            
            if (nextBlockStart) {
                nextBlockStart->prev = blockStart;
            }
            
            prevBlockTail = blockStart;
            curr = nextBlockStart;
        } else {
            int count = 0;
            Node* blockStart = curr;
            
            if (prevBlockTail) {
                prevBlockTail->next = blockStart;
                blockStart->prev = prevBlockTail;
            }
            
            while (count < k && curr) {
                prevBlockTail = curr;
                curr = curr->next;
                count++;
            }
        }
        
        shouldReverse = !shouldReverse;
    }
    
    Node* node = newHead;
    bool first = true;
    while (node) {
        if (!first) cout << ' ';
        cout << node->val;
        first = false;
        node = node->next;
    }
    cout << '\n';
    
    return 0;
}
