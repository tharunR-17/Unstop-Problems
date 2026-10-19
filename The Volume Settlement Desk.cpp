#include <iostream>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

int main() {
    // Optimize standard I/O operations for performance with large inputs
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // Maps ticker ID to its current accumulated total.
    // We use long long for totals because 300,000 operations of 10,000 units 
    // can result in 3,000,000,000, which overflows a standard 32-bit int.
    unordered_map<int, long long> totals;
    
    // Set stores pairs of {-total, ticker_id}
    set<pair<long long, int>> leaderboard;

    for (int i = 0; i < n; ++i) {
        string type;
        cin >> type;

        if (type == "BUY") {
            int id;
            long long units;
            cin >> id >> units;

            // If the ticker already has a positive total, remove its old record from the set
            if (totals[id] > 0) {
                leaderboard.erase({-totals[id], id});
            }

            // Update the total and insert the new updated record into the set
            totals[id] += units;
            leaderboard.insert({-totals[id], id});

        } else if (type == "PEAK") {
            // The current leader is always at the very front of our sorted set
            auto leader = leaderboard.begin();
            
            // Revert the negative sign to get the actual total
            long long leader_total = -(leader->first);
            int leader_id = leader->second;

            // Print the result
            cout << leader_id << " " << leader_total << "\n";

            // Settle the leader: remove them from the set and reset their total to 0
            leaderboard.erase(leader);
            totals[leader_id] = 0;
        }
    }

    return 0;
}
