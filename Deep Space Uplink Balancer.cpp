#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <queue>
#include <map>

using namespace std;

vector<string> process_events(int K, int Q, vector<tuple<int, int, int>> &events){
    // User logic to be implemented here
    priority_queue<pair<long long, int>,vector<pair<long long, int>>,greater<pair<long long, int>>> pq;
    map<int, pair<int, long long>> req;
    vector<string> res;

    for (int i = 1; i <= K; i++)
        pq.push({0, i});

    for (auto event : events){
        int type = get<0>(event);
        int id = get<1>(event);
        int d = get<2>(event);

        if (type == 1){
            auto channel = pq.top();
            pq.pop();

            long long load = channel.first;
            int ch = channel.second;
            req[id] = {ch, d};
            pq.push({load + d, ch});
            res.push_back(to_string(ch));
        }
        else{
            int ch = req[id].first;
            long long d = req[id].second;
            vector<pair<long long, int>> temp;
            long long load = 0;

            while (!pq.empty()){
                auto p = pq.top();
                pq.pop();

                if (p.second == ch)
                    load = p.first - d;
                else
                    temp.push_back(p);
            }

            for (auto p : temp)
                pq.push(p);

            pq.push({load, ch});
            res.push_back(to_string(ch) + " " + to_string(load));
            req.erase(id);
        }
    }
    return res;
}

int main(){
    int K, Q;
    cin >> K >> Q;
    vector<tuple<int, int, int>> events(Q);
    for (int i = 0; i < Q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int id, d;
            cin >> id >> d;
            events[i] = make_tuple(type, id, d);
        } else {
            int id;
            cin >> id;
            events[i] = make_tuple(type, id, 0); // Placeholder for unused value
        }
    }
    vector<string> results = process_events(K, Q, events);
    for (const auto &result : results) {
        cout << result << endl;
    }
    return 0;
}
