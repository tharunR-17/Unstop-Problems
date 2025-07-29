#include <iostream>
#include <vector>

struct Node {
    int val;
    Node* next;
    Node(int v) : val(v), next(nullptr) {}
};

Node* user_logic(Node* head) {
    if (!head || !head->next) return head;

    Node* odd_head = nullptr;
    Node* odd_tail = nullptr;
    Node* even_head = nullptr;
    Node* even_tail = nullptr;

    Node* current = head;

    while (current) {
        if (current->val % 2 != 0) {  // odd
            if (!odd_head) {
                odd_head = odd_tail = current;
            } else {
                odd_tail->next = current;
                odd_tail = odd_tail->next;
            }
        } else {  // even
            if (!even_head) {
                even_head = even_tail = current;
            } else {
                even_tail->next = current;
                even_tail = even_tail->next;
            }
        }
        current = current->next;
    }

    if (odd_tail) {
        odd_tail->next = even_head;
    }
    if (even_tail) {
        even_tail->next = nullptr;
    }

    return odd_head ? odd_head : even_head;
}


Node* create_linked_list(const std::vector<int>& values) {
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int value : values) {
        Node* node = new Node(value);
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}

void linked_list_to_list(Node* head) {
    Node* current = head;
    while (current) {
        std::cout << current->val << " ";
        current = current->next;
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> values[i];
    }
    Node* head = create_linked_list(values);
    Node* new_head = user_logic(head);
    linked_list_to_list(new_head);
    return 0;
}
