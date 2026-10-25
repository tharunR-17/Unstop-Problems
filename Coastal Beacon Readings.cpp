#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

// Node to store in the priority queue
struct PQNode {
    int temp;
    string name;
    long long time;
    int id;

    // Custom comparator to maintain Max-Heap
    bool operator<(const PQNode& other) const {
        if (temp != other.temp) {
            return temp < other.temp; // Higher temperature at the top
        }
        return name > other.name;     // Tie-breaker: Lexicographically smaller name at the top
    }
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    long long T;
    
    if (!(cin >> N >> T)) return 0;

    unordered_map<string, int> current_id;
    priority_queue<PQNode> pq;

    for (int i = 0; i < N; ++i) {
        char type;
        cin >> type;
        
        if (type == 'R') {
            long long time;
            string name;
            int temp;
            cin >> time >> name >> temp;
            
            // Assign a unique ID (the current index) to this transmission
            current_id[name] = i;
            pq.push({temp, name, time, i});
            
        } else if (type == 'Q') {
            long long time;
            cin >> time;

            // Lazily remove outdated or replaced readings from the top of the priority queue
            while (!pq.empty()) {
                auto top = pq.top();
                
                // If this is an old reading that was replaced by the same station
                if (top.id != current_id[top.name]) {
                    pq.pop();
                } 
                // If this reading's valid window has expired
                else if (top.time + T <= time) {
                    pq.pop();
                } 
                // Valid reading found
                else {
                    break;
                }
            }

            if (pq.empty()) {
                cout << "NONE\n";
            } else {
                cout << pq.top().name << " " << pq.top().temp << "\n";
            }
        }
    }

    return 0;
}
