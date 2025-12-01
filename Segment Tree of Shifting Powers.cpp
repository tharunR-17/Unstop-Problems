#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Node {
    int countZeros;
    int maxVal;
};

class SegmentTree {
private:
    int n;
    vector<Node> tree;
    vector<int> arr;

    void pull(int node) {
        tree[node].countZeros = tree[2 * node].countZeros + tree[2 * node + 1].countZeros;
        tree[node].maxVal = max(tree[2 * node].maxVal, tree[2 * node + 1].maxVal);
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node].maxVal = arr[start];
            tree[node].countZeros = (arr[start] == 0) ? 1 : 0;
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        pull(node);
    }

    void update(int node, int start, int end, int l, int r, int x) {
        if (start > end || start > r || end < l) {
            return;
        }

        if (tree[node].maxVal == 0) {
            return;
        }

        if (start == end) {
            arr[start] = arr[start] >> x;
            tree[node].maxVal = arr[start];
            tree[node].countZeros = (arr[start] == 0) ? 1 : 0;
            return;
        }

        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, x);
        update(2 * node + 1, mid + 1, end, l, r, x);
        pull(node);
    }

    int query(int node, int start, int end, int l, int r) {
        if (start > end || start > r || end < l) {
            return 0;
        }
        if (start >= l && end <= r) {
            return tree[node].countZeros;
        }
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, l, r) + 
               query(2 * node + 1, mid + 1, end, l, r);
    }

public:
    SegmentTree(const vector<int>& inputArr) {
        arr = inputArr;
        n = arr.size();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    void updateRange(int l, int r, int x) {
        update(1, 0, n - 1, l, r, x);
    }

    int queryZeros(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

void process_queries(int N, int Q, std::vector<int>& A, std::vector<std::vector<int>>& queries, std::vector<int>& results) {
    SegmentTree st(A);

    for (const auto& q : queries) {
        int type = q[0];
        if (type == 1) {
            int l = q[1];
            int r = q[2];
            int x = q[3];
            st.updateRange(l, r, x);
        } else if (type == 2) {
            int l = q[1];
            int r = q[2];
            int count = st.queryZeros(l, r);
            results.push_back(count);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, Q;
    if (!(std::cin >> N >> Q)) return 0;

    std::vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }

    std::vector<std::vector<int>> queries(Q);
    for (int i = 0; i < Q; ++i) {
        int type;
        std::cin >> type;
        if (type == 1) {
            queries[i] = std::vector<int>(4);
            std::cin >> queries[i][1] >> queries[i][2] >> queries[i][3];
        } else {
            queries[i] = std::vector<int>(3);
            std::cin >> queries[i][1] >> queries[i][2];
        }
        queries[i][0] = type;
    }

    std::vector<int> results;
    process_queries(N, Q, A, queries, results);

    for (const int& result : results) {
        std::cout << result << "\n";
    }

    return 0;
}
