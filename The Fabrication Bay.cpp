#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Order {
    long long profit;
    int deadline;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Order> orders(n);
    for (int i = 0; i < n; ++i) {
        long long p;
        long long d;
        cin >> p >> d;
        // Deadlines larger than n can be capped to n
        orders[i] = {p, (int)min((long long)n, d)};
    }

    // Sort by deadline ascending
    sort(orders.begin(), orders.end(), [](const Order& a, const Order& b) {
        return a.deadline < b.deadline;
    });

    // Min-heap to keep track of the profits of accepted orders
    priority_queue<long long, vector<long long>, greater<long long>> min_heap;

    for (const auto& order : orders) {
        if ((int)min_heap.size() < order.deadline) {
            min_heap.push(order.profit);
        } else if (!min_heap.empty() && min_heap.top() < order.profit) {
            min_heap.pop();
            min_heap.push(order.profit);
        }
    }

    long long total_profit = 0;
    int accepted_count = min_heap.size();

    while (!min_heap.empty()) {
        total_profit += min_heap.top();
        min_heap.pop();
    }

    cout << total_profit << " " << accepted_count << "\n";

    return 0;
}
