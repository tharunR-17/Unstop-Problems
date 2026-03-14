#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>
using namespace std;

typedef tuple<int, int, int, int> Phone;

struct ComparePhone {
    bool operator()(const Phone& p1, const Phone& p2) {
        int id1 = get<0>(p1), arr1 = get<1>(p1), dur1 = get<2>(p1), pri1 = get<3>(p1);
        int id2 = get<0>(p2), arr2 = get<1>(p2), dur2 = get<2>(p2), pri2 = get<3>(p2);
        
        if (pri1 != pri2) return pri1 > pri2;
        if (arr1 != arr2) return arr1 > arr2;
        if (dur1 != dur2) return dur1 > dur2;
        return id1 > id2;
    }
};

vector<int> process_phones(int n, vector<Phone> &phones) {
    sort(phones.begin(), phones.end(), [](const Phone& p1, const Phone& p2) {
        if (get<1>(p1) != get<1>(p2)) return get<1>(p1) < get<1>(p2);
        return get<0>(p1) < get<0>(p2);
    });

    priority_queue<Phone, vector<Phone>, ComparePhone> pq;
    vector<int> result;
    int t = 0;
    int idx = 0;
    
    while (idx < n || !pq.empty()) {
        if (pq.empty() && t < get<1>(phones[idx])) {
            t = get<1>(phones[idx]);
        }
        
        while (idx < n && get<1>(phones[idx]) <= t) {
            pq.push(phones[idx]);
            idx++;
        }
        
        Phone current = pq.top();
        pq.pop();
        
        result.push_back(get<0>(current));
        t += get<2>(current);
    }
    
    return result;
}

int main() {
    int n;
    if (cin >> n) {
        vector<Phone> phones(n);
        for (int i = 0; i < n; i++) {
            int id, arrival, duration, priority;
            cin >> id >> arrival >> duration >> priority;
            phones[i] = make_tuple(id, arrival, duration, priority);
        }
        vector<int> result = process_phones(n, phones);
        for (int i = 0; i < result.size(); ++i) {
            cout << result[i] << (i == result.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}
