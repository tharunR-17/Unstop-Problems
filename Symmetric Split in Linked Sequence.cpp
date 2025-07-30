#include <iostream>
using namespace std;
struct Node {
    int val;
    Node* next;
    Node(int x) : val(x), next(NULL) {}
};

Node* ptr;

bool check(Node* head)
{
    if(head==NULL)
    {
        return true;
    }
    if(!check(head->next))
    {
        return false;
    }
    if(head->val!=ptr->val)
    {
        return false;
    }
    ptr=ptr->next;
    return true;
}

std::string is_symmetric(Node* head) 
{
    ptr=head;
    if(check(head))
    {
        return "YES";
    }
    return "NO";
}

int main() {
    int n;
    std::cin >> n;
    Node *head = nullptr, *tail = nullptr;
    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;
        Node* node = new Node(value);
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    std::string result = is_symmetric(head);
    std::cout << result << std::endl;
    return 0;
}
