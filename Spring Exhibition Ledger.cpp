#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <climits>
using namespace std;


struct Candidate {int prestige, deadline, id;};

bool operator<(const Candidate& a, const Candidate& b) {
    if (a.prestige != b.prestige)
        return a.prestige < b.prestige;
    if (a.deadline != b.deadline)
        return a.deadline < b.deadline;
    return a.id < b.id;
}

struct Node {
    int minSlack, lazy;
    Candidate best;
};

Candidate infinityCandidate() {return {INT_MAX, INT_MAX, INT_MAX};}

struct ST {
    int n;
    vector<Node> tree;

    ST(int size) : n(size), tree(4 * size + 5) {build(1, 1, n);}

    void build(int v, int l, int r) {
        tree[v].lazy = 0;
        tree[v].best = infinityCandidate();

        if (l == r) {
            tree[v].minSlack = l;
            return;
        }

        int m = (l + r) / 2;
        build(v * 2, l, m);
        build(v * 2 + 1, m + 1, r);
        pull(v);
    }

    void pull(int v) {
        tree[v].minSlack = min(tree[v * 2].minSlack, tree[v * 2 + 1].minSlack);
        tree[v].best = min(tree[v * 2].best, tree[v * 2 + 1].best);
    }

    void apply(int v, int value) {
        tree[v].minSlack += value;
        tree[v].lazy += value;
    }

    void push(int v) {
        if (tree[v].lazy == 0)
            return;

        apply(v * 2, tree[v].lazy);
        apply(v * 2 + 1, tree[v].lazy);
        tree[v].lazy = 0;
    }

    void add(int v, int l, int r, int ql, int qr, int value) {
        if (ql <= l && r <= qr) {
            apply(v, value);
            return;
        }

        push(v);
        int m = (l + r) / 2;

        if (ql <= m)
            add(v * 2, l, m, ql, qr, value);

        if (qr > m)
            add(v * 2 + 1, m + 1, r, ql, qr, value);

        pull(v);
    }

    void add(int l, int r, int value) {
        if (l <= r)
            add(1, 1, n, l, r, value);
    }

    void update(int v, int l, int r, int pos, Candidate c) {
        if (l == r) {
            tree[v].best = c;
            return;
        }

        push(v);
        int m = (l + r) / 2;

        if (pos <= m)
            update(v * 2, l, m, pos, c);
        else
            update(v * 2 + 1, m + 1, r, pos, c);

        pull(v);
    }

    void update(int pos, Candidate c) {
        update(1, 1, n, pos, c);
    }

    int firstNegative(int v, int l, int r) {
        if (tree[v].minSlack >= 0)
            return -1;

        if (l == r)
            return l;

        push(v);
        int m = (l + r) / 2;

        if (tree[v * 2].minSlack < 0)
            return firstNegative(v * 2, l, m);

        return firstNegative(v * 2 + 1, m + 1, r);
    }

    int firstNegative() {
        return firstNegative(1, 1, n);
    }

    Candidate query(int v, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return infinityCandidate();

        if (ql <= l && r <= qr)
            return tree[v].best;

        int m = (l + r) / 2;

        return min(
            query(v * 2, l, m, ql, qr),
            query(v * 2 + 1, m + 1, r, ql, qr)
        );
    }

    Candidate query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int N;
    cin >> N;

    ST seg(N);

    using Job = pair<int, int>;
    vector<priority_queue<Job, vector<Job>, greater<Job>>> buckets(N + 1);

    vector<int> prestige(N + 1);
    vector<bool> active(N + 1, false);

    long long total = 0;

    for (int i = 1; i <= N; ++i) {
        int due, pres;
        cin >> due >> pres;

        due = min(due, N);
        prestige[i] = pres;
        active[i] = true;

        buckets[due].push({pres, i});
        total += pres;

        while (!buckets[due].empty() && !active[buckets[due].top().second])
            buckets[due].pop();

        auto best = buckets[due].top();
        seg.update(due, {best.first, due, best.second});
        seg.add(due, N, -1);

        int badDeadline = seg.firstNegative();

        if (badDeadline != -1) {
            Candidate worst = seg.query(1, badDeadline);
            int p = worst.prestige;
            int d = worst.deadline;
            int id = worst.id;
            active[id] = false;
            total -= p;

            while (!buckets[d].empty() && !active[buckets[d].top().second])
                buckets[d].pop();

            if (buckets[d].empty())
                seg.update(d, infinityCandidate());
            else {
                auto bestJob = buckets[d].top();
                seg.update(d, {bestJob.first, d, bestJob.second});
            }
            seg.add(d, N, 1);
        }

        cout << total << (i == N ? '\n' : ' ');
    }

    return 0;
}
