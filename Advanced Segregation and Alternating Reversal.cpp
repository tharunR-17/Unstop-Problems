#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int value;
    Node* nextNode;
    Node(int x) : value(x), nextNode(nullptr) {}
};

Node* alternateReverse(Node* head, int K) {
    Node* current = head;
    Node* previous = nullptr;
    Node* next = nullptr;

    int count = 0;
    Node* temp = head;
    while (temp) {
        count++;
        temp = temp->nextNode;
    }

    bool shouldReverse = true;
    Node* newHead = nullptr;
    Node* tail = nullptr;

    while (count > 0) {
        if (shouldReverse) {
            Node* prevSub = nullptr;
            Node* currSub = current;
            int k = min(K, count);

            for (int i = 0; i < k; i++) {
                next = currSub->nextNode;
                currSub->nextNode = prevSub;
                prevSub = currSub;
                currSub = next;
            }

            if (!newHead) newHead = prevSub;
            if (tail) tail->nextNode = prevSub;
            tail = current;

            current = currSub;
        } else {
            int k = min(K, count);
            if (!newHead) newHead = current;
            if (tail) tail->nextNode = current;

            for (int i = 0; i < k; i++) {
                tail = current;
                current = current->nextNode;
            }
        }

        shouldReverse = !shouldReverse;
        count -= K;
    }

    if (tail) tail->nextNode = nullptr;
    return newHead;
}

Node* mergeLists(Node* list1, Node* list2) {
    Node dummy(0);
    Node* current = &dummy;

    while (list1 && list2) {
        current->nextNode = list1;
        list1 = list1->nextNode;
        current = current->nextNode;

        current->nextNode = list2;
        list2 = list2->nextNode;
        current = current->nextNode;
    }

    if (list1) current->nextNode = list1;
    if (list2) current->nextNode = list2;

    return dummy.nextNode;
}

Node* processList(Node* head, int x, int K) {
    Node* divisibleList = nullptr, * divTail = nullptr;
    Node* nonDivisibleList = nullptr, * nonDivTail = nullptr;

    Node* current = head;
    while (current) {
        if (current->value % x == 0) {
            if (!divisibleList) divisibleList = divTail = current;
            else {
                divTail->nextNode = current;
                divTail = divTail->nextNode;
            }
        } else {
            if (!nonDivisibleList) nonDivisibleList = nonDivTail = current;
            else {
                nonDivTail->nextNode = current;
                nonDivTail = nonDivTail->nextNode;
            }
        }
        current = current->nextNode;
    }

    if (divTail) divTail->nextNode = nullptr;
    if (nonDivTail) nonDivTail->nextNode = nullptr;

    divisibleList = alternateReverse(divisibleList, K);
    nonDivisibleList = alternateReverse(nonDivisibleList, K);

    return mergeLists(divisibleList, nonDivisibleList);
}

void displayList(Node* head) {
    while (head) {
        cout << head->value << " ";
        head = head->nextNode;
    }
    cout << endl;
}

int main() {
    int N, x, K;
    cin >> N;

    Node* head = nullptr;
    Node* tail = nullptr;
    for (int i = 0; i < N; i++) {
        int val;
        cin >> val;
        if (!head) head = tail = new Node(val);
        else {
            tail->nextNode = new Node(val);
            tail = tail->nextNode;
        }
    }

    cin >> x >> K;

    Node* result = processList(head, x, K);
    displayList(result);

    return 0;
}
