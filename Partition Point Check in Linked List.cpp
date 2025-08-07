#include <iostream>
using namespace std;
struct Node {
    int val;
    Node* next;
    Node(int v) : val(v), next(nullptr) {}
};

std::string valid_partition(Node* head, int x) {
    // Write your logic here
    Node*temp=head;
    while(temp!=nullptr){
        if(temp->val<x){
              temp=temp->next;
        }
        else{
            break;
        }
      
        
    }
    if(temp==nullptr){
        return "NO";
    }
    while(temp!=nullptr){
        if(temp->val>=x){
              temp=temp->next;
        }
        else{
            break;
        }
    }
    if(temp==nullptr){
        return "YES";
    }
    
    return "NO";
}

int main() {
    int n, x;
    std::cin >> n >> x;
    
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;
        Node* node = new Node(value);
        if (head == nullptr) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    
    std::string result = valid_partition(head, x);
    std::cout << result << std::endl;

    return 0;
}
