#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Fenwick Tree (Binary Indexed Tree) implementation
struct FenwickTree {
int size;
vector<int> tree;

FenwickTree(int n) : size(n), tree(n + 1, 0) {}

void add(int idx, int delta) {
for (; idx <= size; idx += idx & -idx) {
tree[idx] += delta;
}
}

int query(int idx) {
int sum = 0;
for (; idx > 0; idx -= idx & -idx) {
sum += tree[idx];
}
return sum;
}

// Binary Lifting on BIT to find k-th smallest element in O(log M)
int find_kth(int k) {
int idx = 0;
for (int i = 1 << 19; i > 0; i >>= 1) { // 2^19 > 400000
if (idx + i <= size && tree[idx + i] < k) {
idx += i;
k -= tree[idx];
}
}
return idx + 1; // 1-based index in compressed space
}
};

struct Operation {
char type;
int arg1;
int arg2;
};

int main() {
// Fast I/O
ios_base::sync_with_stdio(false);
cin.tie(NULL);

int n;
if (!(cin >> n)) return 0;

vector<int> initial_prices(n + 1);
vector<int> all_values;
all_values.reserve(n + 200005);

for (int i = 1; i <= n; ++i) {
cin >> initial_prices[i];
all_values.push_back(initial_prices[i]);
}

int q;
cin >> q;

vector<Operation> ops(q);
for (int i = 0; i < q; ++i) {
cin >> ops[i].type;
if (ops[i].type == 'U') {
cin >> ops[i].arg1 >> ops[i].arg2; // i, v
all_values.push_back(ops[i].arg2);
} else if (ops[i].type == 'C') {
cin >> ops[i].arg1; // X
all_values.push_back(ops[i].arg1);
} else if (ops[i].type == 'K') {
cin >> ops[i].arg1; // k
}
}

// Step 1: Coordinate Compression
sort(all_values.begin(), all_values.end());
all_values.erase(unique(all_values.begin(), all_values.end()), all_values.end());

auto get_compressed = [&](int val) -> int {
return lower_bound(all_values.begin(), all_values.end(), val) - all_values.begin() + 1;
};

int m = all_values.size();
FenwickTree bit(m);

// Track current stall prices
vector<int> current_prices(n + 1);
for (int i = 1; i <= n; ++i) {
current_prices[i] = initial_prices[i];
bit.add(get_compressed(initial_prices[i]), 1);
}

// Step 2: Process Queries
for (int i = 0; i < q; ++i) {
if (ops[i].type == 'U') {
int stall_idx = ops[i].arg1;
int new_val = ops[i].arg2;

int old_comp = get_compressed(current_prices[stall_idx]);
int new_comp = get_compressed(new_val);

bit.add(old_comp, -1);
bit.add(new_comp, 1);
current_prices[stall_idx] = new_val;

} else if (ops[i].type == 'C') {
int X = ops[i].arg1;
// Find the rightmost value <= X
auto it = upper_bound(all_values.begin(), all_values.end(), X);
int comp_idx = it - all_values.begin(); // Number of values <= X

cout << bit.query(comp_idx) << "\n";

} else if (ops[i].type == 'K') {
int k = ops[i].arg1;
int comp_idx = bit.find_kth(k);
cout << all_values[comp_idx - 1] << "\n";
}
}

return 0;
}
