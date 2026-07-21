#include <iostream>
#include <vector>

using namespace std;

// Structure for a BST Node
struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// Function to insert an artifact number into the BST
Node* insert(Node* root, int val) {
    if (root == nullptr) {
        return new Node(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

// Function for Post-order Traversal (Left -> Right -> Root)
void postOrder(Node* root, vector<int>& sequence) {
    if (root == nullptr) {
        return;
    }
    postOrder(root->left, sequence);
    postOrder(root->right, sequence);
    sequence.push_back(root->data);
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    Node* root = nullptr;
    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        root = insert(root, val);
    }
    
    // Generate the recovery sequence
    vector<int> result;
    postOrder(root, result);
    
    // Print the output sequence
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << (i == result.size() - 1 ? "" : " ");
    }
    cout << "\n";
    
    return 0;
}
