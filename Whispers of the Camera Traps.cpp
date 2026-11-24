#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long W;
    cin >> n >> W;

    vector<int> freq(200001, 0);

    // Stores {sighting_time, species_id}
    queue<pair<long long, int>> q;

    // Stores {-frequency, species_id}
    set<pair<int, int>> st;

    for (int i = 0; i < n; i++) {

        char type;
        long long t;
        cin >> type >> t;

        // Remove expired sightings
        while (!q.empty() && q.front().first <= t - W) {

            int id = q.front().second;
            q.pop();

            st.erase({-freq[id], id});

            freq[id]--;

            if (freq[id] > 0) {
                st.insert({-freq[id], id});
            }
        }

        if (type == 'S') {

            int id;
            cin >> id;

            q.push({t, id});

            if (freq[id] > 0) {
                st.erase({-freq[id], id});
            }

            freq[id]++;

            st.insert({-freq[id], id});
        }

        else if (type == 'Q') {

            if (st.empty()) {
                cout << "QUIET\n";
            }
            else {
                auto ans = *st.begin();

                cout << ans.second << " "
                     << -ans.first << "\n";
            }
        }
    }

    return 0;
}
