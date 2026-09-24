#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Event {
    string type;
    string code_or_prefix;
    int era;
};

vector<int> process_events(const vector<Event>& events) {
    // User should implement their logic here

    vector<pair<string, int>> shards;
    vector<int> results;

    for(const auto &event: events){
        if(event.type == "ADD"){
            shards.push_back({event.code_or_prefix, event.era});
        }
        if(event.type == "QUERY"){
            int count = 0;
            for(const auto &shard: shards){
                const string& code = shard.first;
                int era = shard.second;

                if(code.compare(0, event.code_or_prefix.size(), event.code_or_prefix)== 0 && (era == event.era)){
                    ++count;
                }
            }
            results.push_back(count);
        }
        
    }
    
    return results;
}

int main() {
    int Q;
    cin >> Q;
    vector<Event> events(Q);

    for (int i = 0; i < Q; ++i) {
        cin >> events[i].type >> events[i].code_or_prefix >> events[i].era;
    }

    vector<int> results = process_events(events);

    for (int result : results) {
        cout << result << endl;
    }

    return 0;
}
