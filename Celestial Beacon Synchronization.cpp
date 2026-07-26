#include <bits/stdc++.h>
using namespace std;

struct Query {
    int l, r, idx;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<int> a(N + 1);
    for (int i = 1; i <= N; i++)
        cin >> a[i];

    int block = sqrt(N);

    vector<Query> queries(Q);
    for (int i = 0; i < Q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].idx = i;
    }

    sort(queries.begin(), queries.end(), [&](Query &A, Query &B) {
        int blockA = A.l / block;
        int blockB = B.l / block;

        if (blockA != blockB)
            return blockA < blockB;

        if (blockA & 1)
            return A.r > B.r;
        return A.r < B.r;
    });

    vector<long long> ans(Q);
    unordered_map<int, long long> freq;

    long long curAns = 0;
    int curL = 1, curR = 0;

    auto add = [&](int idx) {
        long long f = freq[a[idx]];
        curAns -= f * f;
        f++;
        freq[a[idx]] = f;
        curAns += f * f;
    };

    auto remove = [&](int idx) {
        long long f = freq[a[idx]];
        curAns -= f * f;
        f--;
        freq[a[idx]] = f;
        curAns += f * f;
    };

    for (auto &q : queries) {
        while (curL > q.l) add(--curL);
        while (curR < q.r) add(++curR);
        while (curL < q.l) remove(curL++);
        while (curR > q.r) remove(curR--);

        ans[q.idx] = curAns;
    }

    for (long long x : ans)
        cout << x << "\n";

    return 0;
}
