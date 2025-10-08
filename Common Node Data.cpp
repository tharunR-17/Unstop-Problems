#include <iostream>
#include <vector>
using namespace std;

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Function to create linked list from vector
ListNode* createLinkedList(const vector<int>& values) {
    if (values.empty()) return nullptr;
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    for (int i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    return head;
}

// Function to find the first common node
int findFirstCommonNode(ListNode* head1, ListNode* head2) {
    // Get lengths of both lists
    ListNode* temp1 = head1;
    ListNode* temp2 = head2;
    int len1 = 0, len2 = 0;

    // Calculate length of the first list
    while (temp1 != nullptr) {
        len1++;
        temp1 = temp1->next;
    }

    // Calculate length of the second list
    while (temp2 != nullptr) {
        len2++;
        temp2 = temp2->next;
    }

    // Align the longer list's head
    temp1 = head1;
    temp2 = head2;
    if (len1 > len2) {
        for (int i = 0; i < (len1 - len2); i++) {
            temp1 = temp1->next;
        }
    } else if (len2 > len1) {
        for (int i = 0; i < (len2 - len1); i++) {
            temp2 = temp2->next;
        }
    }

    // Traverse both lists together and find the first common node
    while (temp1 != nullptr && temp2 != nullptr) {
        if (temp1->val == temp2->val) {
            return temp1->val;  // Return the value of the first common node
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return -1;  // No common node found
}

int main() {
    int size1, size2;
    cin >> size1 >> size2;

    vector<int> list1(size1), list2(size2);

    // Input elements of linked list 1
    for (int i = 0; i < size1; i++) {
        cin >> list1[i];
    }

    // Input elements of linked list 2
    for (int i = 0; i < size2; i++) {
        cin >> list2[i];
    }

    // Create linked lists from the input vectors
    ListNode* head1 = createLinkedList(list1);
    ListNode* head2 = createLinkedList(list2);

    // Find and print the first common node
    int result = findFirstCommonNode(head1, head2);
    cout << result << endl;

    return 0;
}
