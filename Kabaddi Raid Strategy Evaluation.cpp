#include <bits/stdc++.h>
using namespace std;

struct RaidResult {
    int index;
    int staminaUsed;
    
    RaidResult(int idx, int used) : index(idx), staminaUsed(used) {}
};

vector<int> evaluate_raids(int n, vector<string>& raids, vector<int>& stamina) {
    vector<RaidResult> successful;

    for (int i = 0; i < n; ++i) {
        string& raid = raids[i];
        int limit = stamina[i];
        int used = 0;
        bool hasTouch = false;
        bool valid = true;

        for (int j = 0; j < raid.size(); ++j) {
            char move = raid[j];
            if (move == 'T') {
                used += 3;
                hasTouch = true;
            } else if (move == 'F') {
                used += 1;
            } else if (move == 'R') {
                used += 2;
                if (j > 0 && raid[j - 1] == 'R') {
                    valid = false;
                    break;
                }
            } else {
                valid = false;
                break;
            }

            if (used > limit) {
                valid = false;
                break;
            }
        }

        if (valid && hasTouch && raid.back() == 'R' && used <= limit) {
            successful.emplace_back(i, used);
        }
    }
    stable_sort(successful.begin(), successful.end(), [](const RaidResult& a, const RaidResult& b) {
        return a.staminaUsed < b.staminaUsed;
    });

    vector<int> result;
    for (auto& r : successful) {
        result.push_back(r.index);
    }

    return result;
}

int main() {
    int n;
    cin >> n;
    vector<string> raids(n);
    for (int i = 0; i < n; ++i) {
        cin >> raids[i];
    }

    vector<int> stamina(n);
    for (int i = 0; i < n; ++i) {
        cin >> stamina[i];
    }

    vector<int> result = evaluate_raids(n, raids, stamina);

    for (int idx : result) {
        cout << idx << " ";
    }
    cout << endl;

    return 0;
}
