#include <stdio.h>
#include <string.h>

#define MAX 400005

typedef struct {
    int level;
    int id;
} Node;

Node heap[MAX];
int sz = 0;

int battery[MAX];
int active[MAX];

void swap(Node *a, Node *b) {
    Node t = *a;
    *a = *b;
    *b = t;
}

int smaller(Node a, Node b) {
    if (a.level != b.level)
        return a.level < b.level;
    return a.id < b.id;
}

void push(int level, int id) {
    int i = ++sz;

    heap[i].level = level;
    heap[i].id = id;

    while (i > 1 && smaller(heap[i], heap[i / 2])) {
        swap(&heap[i], &heap[i / 2]);
        i /= 2;
    }
}

Node pop() {
    Node result = heap[1];
    heap[1] = heap[sz--];

    int i = 1;

    while (1) {
        int l = 2 * i;
        int r = 2 * i + 1;
        int s = i;

        if (l <= sz && smaller(heap[l], heap[s]))
            s = l;

        if (r <= sz && smaller(heap[r], heap[s]))
            s = r;

        if (s == i)
            break;

        swap(&heap[i], &heap[s]);
        i = s;
    }

    return result;
}

int main() {
    int N, E;
    scanf("%d %d", &N, &E);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &battery[i]);
        active[i] = 1;
        push(battery[i], i);
    }

    char op[20];

    for (int i = 0; i < E; i++) {
        scanf("%s", op);

        if (strcmp(op, "DRAIN") == 0) {
            int id, amount;
            scanf("%d %d", &id, &amount);

            battery[id] -= amount;

            if (battery[id] < 0)
                battery[id] = 0;

            push(battery[id], id);
        }

        else if (strcmp(op, "RETIRE") == 0) {
            int id;
            scanf("%d", &id);

            active[id] = 0;
        }

        else if (strcmp(op, "SERVICE") == 0) {

            while (sz > 0) {
                Node top = heap[1];

                if (!active[top.id] ||
                    battery[top.id] != top.level) {
                    pop();
                } else {
                    break;
                }
            }

            if (sz == 0) {
                printf("NONE\n");
            } else {
                Node chosen = pop();

                printf("%d\n", chosen.id);

                battery[chosen.id] = 100;

                push(100, chosen.id);
            }
        }
    }

    return 0;
}
