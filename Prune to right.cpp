#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void user_logic(int t, vector<pair<int, vector<int>>>& test_cases) {
    for (int i = 0; i < t; i++) {
        int N = test_cases[i].first;
        vector<int>& arr = test_cases[i].second;
        int n = arr.size();
        if (n == 0) { cout << "\n"; continue; }
        vector<TreeNode*> nodes(n);
        for (int j = 0; j < n; j++) nodes[j] = new TreeNode(arr[j]);
        for (int j = 0; j < n; j++) {
            int l = 2*j+1, r = 2*j+2;
            if (l < n) nodes[j]->left = nodes[l];
            if (r < n) nodes[j]->right = nodes[r];
        }
        for (int j = 0; j < n; j++) nodes[j]->right = NULL;
        vector<int> result;
        vector<TreeNode*> stk;
        stk.push_back(nodes[0]);
        while (!stk.empty()) {
            TreeNode* cur = stk.back(); stk.pop_back();
            result.push_back(cur->val);
            if (cur->right) stk.push_back(cur->right);
            if (cur->left) stk.push_back(cur->left);
        }
        for (int j = 0; j < (int)result.size(); j++) {
            if (j) cout << " ";
            cout << result[j];
        }
        cout << "\n";
        for (int j = 0; j < n; j++) delete nodes[j];
    }
}

int main() {
    int t;
    cin >> t;
    vector<pair<int, vector<int>>> test_cases(t);
    for (int i = 0; i < t; ++i) {
        int N;
        cin >> N;
        int number_of_nodes = (1 << N) - 1;
        vector<int> arr(number_of_nodes);
        for (int j = 0; j < number_of_nodes; ++j) cin >> arr[j];
        test_cases[i] = make_pair(N, arr);
    }
    user_logic(t, test_cases);
    return 0;
}
