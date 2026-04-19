#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MAXB 31

int A[MAXN];

typedef struct {
    int basis[MAXB];
} Basis;

void init(Basis* b) {
    memset(b->basis, 0, sizeof(b->basis));
}

void insert(Basis* b, int x) {
    for (int i = MAXB - 1; i >= 0; i--) {
        if (!(x & (1 << i))) continue;

        if (!b->basis[i]) {
            b->basis[i] = x;
            return;
        }

        x ^= b->basis[i];
    }
}

int getMin(Basis* b, int x) {
    for (int i = MAXB - 1; i >= 0; i--) {
        if (b->basis[i] && (x ^ b->basis[i]) < x) {
            x ^= b->basis[i];
        }
    }
    return x;
}

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }

    while (Q--) {
        int l, r, x;
        scanf("%d %d %d", &l, &r, &x);

        Basis b;
        init(&b);

        for (int i = l; i <= r; i++) {
            insert(&b, A[i]);
        }

        printf("%d\n", getMin(&b, x));
    }

    return 0;
}
