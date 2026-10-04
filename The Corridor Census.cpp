#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

struct Query {
    int l, r, id;
};

int main() {

    int n, q;
    cin >> n >> q;

    vector<int> a(n);

    for (int &x : a)
        cin >> x;
    vector<int> values = a;
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    for (int &x : a) {
        x = lower_bound(values.begin(), values.end(), x)
            - values.begin();
    }

    vector<Query> queries(q);

    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--;
        queries[i].r--;

        queries[i].id = i;
    }

    int bs = sqrt(n) + 1;

    sort(queries.begin(), queries.end(),
        [&](const Query &x, const Query &y) {

            int bx = x.l / bs;
            int by = y.l / bs;

            if (bx != by)
                return bx < by;
            if (bx & 1)
                return x.r > y.r;

            return x.r < y.r;
        });

    int distinct = values.size();

    vector<int> freq(distinct, 0);
    vector<int> countFreq(n + 1, 0);

    vector<int> answer(q);

    int curL = 0;
    int curR = -1;

    int maxFreq = 0;

    auto add = [&](int pos) {
        int x = a[pos];

        int oldFreq = freq[x];

        if (oldFreq > 0)
            countFreq[oldFreq]--;

        freq[x]++;

        int newFreq = freq[x];

        countFreq[newFreq]++;

        maxFreq = max(maxFreq, newFreq);
    };

    auto remove = [&](int pos) {
        int x = a[pos];

        int oldFreq = freq[x];

        countFreq[oldFreq]--;

        freq[x]--;

        int newFreq = freq[x];

        if (newFreq > 0)
            countFreq[newFreq]++;

        while (maxFreq > 0 && countFreq[maxFreq] == 0)
            maxFreq--;
    };

    for (auto &query : queries) {

        int l = query.l;
        int r = query.r;

        while (curL > l)
            add(--curL);

        while (curR < r)
            add(++curR);

        while (curL < l)
            remove(curL++);

        while (curR > r)
            remove(curR--);

        answer[query.id] = maxFreq;
    }

    for (int x : answer)
        cout << x << endl;

    return 0;
}
