#include <iostream>
#include <vector>
using namespace std;

struct SegmentNode {
    long long sum;
    SegmentNode *leftChild, *rightChild;

    SegmentNode(long long s = 0) : sum(s), leftChild(nullptr), rightChild(nullptr) {}

    SegmentNode(SegmentNode* l, SegmentNode* r) : leftChild(l), rightChild(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

SegmentNode* buildTree(const vector<int>& data, int low, int high) {
    if (low == high) return new SegmentNode(data[low]);
    int mid = (low + high) / 2;
    return new SegmentNode(buildTree(data, low, mid), buildTree(data, mid + 1, high));
}

SegmentNode* modify(SegmentNode* prevRoot, int low, int high, int pos, int newVal) {
    if (low == high) return new SegmentNode(newVal);
    int mid = (low + high) / 2;
    if (pos <= mid)
        return new SegmentNode(modify(prevRoot->leftChild, low, mid, pos, newVal), prevRoot->rightChild);
    else
        return new SegmentNode(prevRoot->leftChild, modify(prevRoot->rightChild, mid + 1, high, pos, newVal));
}

long long rangeQuery(SegmentNode* node, int low, int high, int qLow, int qHigh) {
    if (!node || qHigh < low || high < qLow) return 0;
    if (qLow <= low && high <= qHigh) return node->sum;
    int mid = (low + high) / 2;
    return rangeQuery(node->leftChild, low, mid, qLow, qHigh) + rangeQuery(node->rightChild, mid + 1, high, qLow, qHigh);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, queries;
    cin >> n >> queries;
    vector<int> values(n);
    for (auto &val : values) cin >> val;

    vector<SegmentNode*> versions;
    versions.push_back(buildTree(values, 0, n - 1));

    while (queries--) {
        int type, version;
        cin >> type >> version;
        if (type == 1) {
            int idx, val;
            cin >> idx >> val;
            versions.push_back(modify(versions[version - 1], 0, n - 1, idx - 1, val));
        } else {
            int left, right;
            cin >> left >> right;
            cout << rangeQuery(versions[version - 1], 0, n - 1, left - 1, right - 1) << '\n';
        }
    }
}
