#include <bits/stdc++.h>
using namespace std;

struct Info {
    int count = 0;
    int firstPos = -1;
};

struct Person {
    long long id;
    int count;
    int firstPos;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    unordered_map<long long, Info> mp;

    for (int i = 1; i <= N; i++) {
        char operation;
        long long id;

        cin >> operation >> id;

        if (operation == '+') {
            // First ever '+' scan for this ID.
            if (mp.find(id) == mp.end()) {
                mp[id] = {1, i};
            } else {
                mp[id].count++;
            }
        } else {
            // Guaranteed that current count is positive.
            mp[id].count--;
        }
    }

    vector<Person> candidates;

    for (const auto& entry : mp) {
        long long id = entry.first;
        const Info& info = entry.second;

        // Only positive final net counts qualify.
        if (info.count > 0) {
            candidates.push_back({
                id,
                info.count,
                info.firstPos
            });
        }
    }

    sort(candidates.begin(), candidates.end(),
         [](const Person& a, const Person& b) {
             // Higher net count comes first.
             if (a.count != b.count) {
                 return a.count > b.count;
             }

             // Earlier first '+' scan comes first.
             return a.firstPos < b.firstPos;
         });

    int answerCount = min(K, (int)candidates.size());

    for (int i = 0; i < answerCount; i++) {
        cout << candidates[i].id << ' '
             << candidates[i].count << '\n';
    }

    return 0;
}
