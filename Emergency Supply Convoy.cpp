#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<pair<int, long long>> jobs(N);

    for (int i = 0; i < N; i++) {
        int D;
        long long C;
        cin >> D >> C;
        jobs[i] = {D, C};
    }

    sort(jobs.begin(), jobs.end());

    priority_queue<long long, vector<long long>, greater<long long>> pq;

    long long total = 0;

    for (auto [deadline, crates] : jobs) {
        pq.push(crates);
        total += crates;

        // Cannot schedule more than 'deadline' jobs
        if ((int)pq.size() > deadline) {
            total -= pq.top();
            pq.pop();
        }
    }

    cout << total << '\n';

    return 0;
}
