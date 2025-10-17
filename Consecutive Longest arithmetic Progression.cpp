#include <bits/stdc++.h>
using namespace std;
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

int longest_arithmetic_progression(ListNode* head) {
    // Write your logic here.
    // Parameters:
    //     head (ListNode*): Head node of the linked list
    // Returns:
    //     int: Longest length of arithmetic progression with consecutive elements
    if(!head -> next)
        return 1;
    if(!head -> next -> next)
        return 2;
    int result = 2;
    ListNode *last = head -> next;
    ListNode *p = head -> next -> next;
    int count = 2, diff = last -> val - head -> val;
    while(p){
        if((p -> val - last -> val) != diff){
            diff = p -> val - last -> val;
            count = 2;
        }else{
            count++;
        }
            result = max(result, count);
        p = p -> next;
        last = last -> next;
    }
    return result;
}

int main() {
    int n;
    std::cin >> n;
    if (n == 0) {
        std::cout << 0 << std::endl;
        return 0;
    }
    
    std::vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> values[i];
    }
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    for (int i = 1; i < n; ++i) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    
    int result = longest_arithmetic_progression(head);
    std::cout << result << std::endl;
    
    // Free memory
    current = head;
    while (current != NULL) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
    return 0;
}
