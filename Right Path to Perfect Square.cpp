#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <string>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Function to check if a number is a perfect square
bool isPerfectSquare(int num) {
    int root = sqrt(num);
    return root * root == num;
}

// Build a binary tree from level order traversal
TreeNode* buildTree(vector<string>& nodes) {
    if (nodes.empty() || nodes[0] == "N") return NULL;

    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;

    while (!q.empty() && i < nodes.size()) {
        TreeNode* curr = q.front();
        q.pop();

        if (nodes[i] != "N") {
            curr->left = new TreeNode(stoi(nodes[i]));
            q.push(curr->left);
        }
        i++;

        if (i < nodes.size() && nodes[i] != "N") {
            curr->right = new TreeNode(stoi(nodes[i]));
            q.push(curr->right);
        }
        i++;
    }

    return root;
}

// Calculate the sum of values along the rightmost path
int rightPathSum(TreeNode* root) {
    int sum = 0;
    while (root) {
        sum += root->val;
        root = root->right;
    }
    return sum;
}

int main() {
    int n;
    cin >> n;
    vector<string> nodes(n);

    for (int i = 0; i < n; i++) {
        cin >> nodes[i];
    }

    TreeNode* root = buildTree(nodes);
    int sum = rightPathSum(root);

    if (isPerfectSquare(sum)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
