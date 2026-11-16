#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int Q;
    cin >> Q;
    
    set<pair<long long, long long>> batches; // {lastDay, id}
    map<long long, pair<long long, long long>> info; // id -> {lastDay, remaining}
    
    long long wasted = 0;
    
    for (int i = 0; i < Q; i++) {
        char type;
        cin >> type;
        
        if (type == 'R') {
            long long id, lastDay, doses;
            cin >> id >> lastDay >> doses;
            batches.insert({lastDay, id});
            info[id] = {lastDay, doses};
        } else if (type == 'I') {
            long long day, doses;
            cin >> day >> doses;
            
            // Discard expired batches
            while (!batches.empty()) {
                auto it = batches.begin();
                long long ld = it->first;
                long long id = it->second;
                if (ld >= day) break;
                // expired
                wasted += info[id].second;
                batches.erase(it);
                info.erase(id);
            }
            
            // Serve the request
            long long need = doses;
            long long supplied = 0;
            
            while (need > 0 && !batches.empty()) {
                auto it = batches.begin();
                long long id = it->second;
                long long &rem = info[id].second;
                
                if (rem <= need) {
                    supplied += rem;
                    need -= rem;
                    batches.erase(it);
                    info.erase(id);
                } else {
                    rem -= need;
                    supplied += need;
                    need = 0;
                }
            }
            
            cout << supplied << " " << (doses - supplied) << "\n";
        } else if (type == 'C') {
            long long id;
            cin >> id;
            if (info.count(id)) {
                long long ld = info[id].first;
                batches.erase({ld, id});
                info.erase(id);
            }
        }
    }
    
    cout << "wasted " << wasted << "\n";
    
    return 0;
}
