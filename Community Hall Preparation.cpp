#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Fast I/O for performance on large inputs (N = 200,000)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    // Store events as pairs of {time, event_type}
    // event_type = 1 for a team starting
    // event_type = -1 for a team ending
    vector<pair<int, int>> events;
    events.reserve(2 * n);
    
    for (int i = 0; i < n; ++i) {
        int s, e;
        cin >> s >> e;
        events.push_back({s, 1});
        events.push_back({e, -1});
    }
    
    // Sort the events. 
    // std::sort on pairs prioritizes the first element (time).
    // If times are tied, it sorts by the second element (event_type).
    // Because -1 (end) < 1 (start), ends are automatically processed before 
    // starts at the exact same time, resolving the non-conflicting boundary rule.
    sort(events.begin(), events.end());
    
    int current_zones = 0;
    int min_zones_required = 0;
    
    // Sweep through the timeline
    for (const auto& event : events) {
        current_zones += event.second;
        if (current_zones > min_zones_required) {
            min_zones_required = current_zones;
        }
    }
    
    cout << min_zones_required << "\n";
    
    return 0;
}
