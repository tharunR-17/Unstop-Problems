#include <bits/stdc++.h>
using namespace std;

/**
 * Returns {max_count, max_priority} under the lexicographic objective:
 *  1) maximize count
 *  2) subject to that, maximize total priority
 */
pair<int, long long> max_orders(int n, long long T, vector<pair<int,int>>& orders) {
    // Phase 1: find the maximum k such that the sum of the k smallest processing‐times ≤ T
    vector<int> times(n);
    for (int i = 0; i < n; i++) 
        times[i] = orders[i].first;
    sort(times.begin(), times.end());

    long long sum_t = 0;
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (sum_t + times[i] <= T) {
            sum_t += times[i];
            k++;
        } else {
            break;
        }
    }
    if (k == 0) 
        return make_pair(0, 0LL);

    // Phase 2: among all subsets of exactly k items with total time ≤ T,
    // find the one with the largest total priority.
    // We scan in descending-priority order, and keep a max‐heap of
    // the k smallest‐time items seen so far.
    sort(orders.begin(), orders.end(),
         [](const pair<int,int>& a, const pair<int,int>& b){
             return a.second > b.second;
         });

    // max-heap by processing‐time
    priority_queue< pair<int,int> > pq;
    long long cur_time = 0, cur_prio = 0, best_prio = 0;

    for (int i = 0; i < n; i++) {
        int t = orders[i].first;
        int p = orders[i].second;

        pq.push(make_pair(t, p));
        cur_time += t;
        cur_prio += p;

        // if we have more than k items, drop the one with the largest time
        if ((int)pq.size() > k) {
            pair<int,int> top = pq.top();
            pq.pop();
            cur_time -= top.first;
            cur_prio -= top.second;
        }

        // whenever we have exactly k items and they fit in T, consider updating
        if ((int)pq.size() == k && cur_time <= T) {
            best_prio = max(best_prio, cur_prio);
        }
    }

    return make_pair(k, best_prio);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long T;
    cin >> n >> T;
    vector<pair<int,int>> orders(n);
    for (int i = 0; i < n; i++) {
        cin >> orders[i].first >> orders[i].second;
    }

    pair<int,long long> ans = max_orders(n, T, orders);
    cout << ans.first << " " << ans.second << "\n";
    return 0;
}
