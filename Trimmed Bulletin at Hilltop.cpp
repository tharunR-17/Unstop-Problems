#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

typedef long long ll;

typedef struct {
    ll t, v;
} Reading;

typedef struct {
    ll t;
    int p;
} Bulletin;

Reading a[MAXN];
Bulletin b[MAXN];

ll vals[MAXN];
ll bitSum[MAXN];
int bitCnt[MAXN];

int n, q, W, sz;

int cmpLL(const void *x, const void *y) {
    ll a = *(ll *)x;
    ll b = *(ll *)y;
    return (a > b) - (a < b);
}

void update(int i, int dc, ll ds) {
    while (i <= sz) {
        bitCnt[i] += dc;
        bitSum[i] += ds;
        i += i & -i;
    }
}

ll querySum(int i) {
    ll s = 0;
    while (i > 0) {
        s += bitSum[i];
        i -= i & -i;
    }
    return s;
}

int queryCount(int i) {
    int s = 0;
    while (i > 0) {
        s += bitCnt[i];
        i -= i & -i;
    }
    return s;
}

int kth(int k) {
    int pos = 0;
    int step = 1;

    while ((step << 1) <= sz)
        step <<= 1;

    for (; step; step >>= 1) {
        int next = pos + step;

        if (next <= sz && bitCnt[next] < k) {
            pos = next;
            k -= bitCnt[next];
        }
    }

    return pos + 1;
}

ll sumSmallest(int k) {
    if (k <= 0) return 0;

    int pos = 0;
    int cnt = 0;
    ll sum = 0;

    int step = 1;
    while ((step << 1) <= sz)
        step <<= 1;

    for (; step; step >>= 1) {
        int next = pos + step;

        if (next <= sz && cnt + bitCnt[next] < k) {
            pos = next;
            cnt += bitCnt[next];
            sum += bitSum[next];
        }
    }

    int idx = pos + 1;

    return sum + (ll)(k - cnt) * vals[idx - 1];
}

int getIndex(ll v) {
    int l = 0, r = sz - 1;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (vals[mid] == v)
            return mid + 1;

        if (vals[mid] < v)
            l = mid + 1;
        else
            r = mid - 1;
    }

    return -1;
}

int main() {
    scanf("%d %d %d", &n, &q, &W);

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &a[i].t, &a[i].v);
        vals[i] = a[i].v;
    }

    for (int i = 0; i < q; i++) {
        scanf("%lld %d", &b[i].t, &b[i].p);
    }

    qsort(vals, n, sizeof(ll), cmpLL);

    sz = 0;

    for (int i = 0; i < n; i++) {
        if (sz == 0 || vals[i] != vals[sz - 1]) {
            vals[sz++] = vals[i];
        }
    }

    int add = 0, rem = 0;
    int total = 0;

    ll totalSum = 0;

    for (int i = 0; i < q; i++) {

        ll t = b[i].t;
        int p = b[i].p;

        // Add all readings available by time t
        while (add < n && a[add].t <= t) {
            int id = getIndex(a[add].v);

            update(id, 1, a[add].v);

            total++;
            totalSum += a[add].v;

            add++;
        }

        // Remove expired readings
        while (rem < add && t - a[rem].t >= W) {
            int id = getIndex(a[rem].v);

            update(id, -1, -a[rem].v);

            total--;
            totalSum -= a[rem].v;

            rem++;
        }

        if (total == 0) {
            printf("NO DATA\n");
            continue;
        }

        int k = (total * p) / 100;

        int kept = total - 2 * k;

        ll sum = sumSmallest(total - k)
               - sumSmallest(k);

        int minIdx = kth(k + 1);
        int maxIdx = kth(total - k);

        ll minimum = vals[minIdx - 1];
        ll maximum = vals[maxIdx - 1];

        printf("%d %lld %lld %lld\n",
               kept, sum, minimum, maximum);
    }

    return 0;
}
