#include <iostream>
#include <vector>

struct Node {
    int data;
    Node* next;
    Node(int data) : data(data), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;
    Node* tail;

    LinkedList() : head(nullptr), tail(nullptr) {}

    void push(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void printList() {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

void user_logic(LinkedList &linkedList) {
    if (!linkedList.head || !linkedList.head->next || !linkedList.head->next->next)
        return;

    Node *first = nullptr, *fTail = nullptr;
    Node *second = nullptr, *sTail = nullptr;
    Node *third = nullptr, *tTail = nullptr;

    Node* curr = linkedList.head;
    int pos = 1;

    while (curr) {
        Node* nextNode = curr->next;
        curr->next = nullptr;

        if (pos % 3 == 1) {                    // 1st group
            if (!first) first = curr;
            else fTail->next = curr;
            fTail = curr;
        } 
        else if (pos % 3 == 2) {               // 2nd group
            if (!second) second = curr;
            else sTail->next = curr;
            sTail = curr;
        } 
        else {                                 // 3rd group
            if (!third) third = curr;
            else tTail->next = curr;
            tTail = curr;
        }

        curr = nextNode;
        pos++;
    }

    // Merge first → second → third
    if (fTail) fTail->next = second;
    if (sTail) sTail->next = third;

    linkedList.head = first;
}
int main() {
    int n;
    std::cin >> n;

    LinkedList list;
    for (int i = 0; i < n; ++i) {
        int element;
        std::cin >> element;
        list.push(element);
    }

    user_logic(list);
    list.printList();

    return 0;
}
