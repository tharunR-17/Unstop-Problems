#include <bits/stdc++.h>
using namespace std;

// Element to be stored in the priority queue
struct Element {
    int score;
    int tag;
    long long event_id;
    long long time;

    // Custom comparator to enforce Max-Heap properties
    bool operator<(const Element& other) const {
        if (score != other.score) 
            return score < other.score; // Highest score at the top
        return tag > other.tag;         // Tie-breaker: Smallest tag at the top
    }
};

int main() {
    // Optimize standard I/O operations for competitive programming
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long W;
    if (!(cin >> N >> W)) return 0;

    unordered_map<int, long long> latest_sighting;
    priority_queue<Element> pq;
    long long current_event_id = 0;

    for (int i = 0; i < N; ++i) {
        char type;
        cin >> type;
        
        if (type == 'S') {
            long long t;
            int tag, score;
            cin >> t >> tag >> score;
            
            ++current_event_id;
            latest_sighting[tag] = current_event_id;
            pq.push({score, tag, current_event_id, t});
            
        } else if (type == 'R') {
            long long t;
            int tag;
            cin >> t >> tag;
            
            // Mark the tag as absent by setting its latest event_id to -1.
            // This invalidates all existing instances of this tag in the PQ.
            latest_sighting[tag] = -1;
            
        } else if (type == 'Q') {
            long long t;
            cin >> t;
            
            // Lazy deletion: Clean up invalid or expired elements from the top
            while (!pq.empty()) {
                const auto& top = pq.top();
                
                if (latest_sighting[top.tag] != top.event_id || top.time < t - W) {
                    pq.pop();
                } else {
                    break;
                }
            }
            
            // Answer the query
            if (pq.empty()) {
                cout << "EMPTY\n";
            } else {
                cout << pq.top().tag << " " << pq.top().score << "\n";
            }
        }
    }

    return 0;
}
