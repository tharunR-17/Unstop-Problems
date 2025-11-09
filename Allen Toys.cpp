#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

bool isAnagram(unordered_map<char, int>& a, unordered_map<char, int>& b) {
    for (auto& pair : b) {
        if (a[pair.first] != pair.second) {
            return false;
        }
    }
    return true;
}

int main() {
    string s, p;
    cin >> s >> p;

    int n = s.size(), m = p.size();

    if (m > n) {
        cout << 0 << endl;
        cout << "none" << endl;
        return 0;
    }

    unordered_map<char, int> pCount, sCount;

    for (char c : p) pCount[c]++;
    for (int i = 0; i < m; i++) sCount[s[i]]++;

    vector<int> result;

    if (isAnagram(sCount, pCount)) {
        result.push_back(1);
    }

    for (int i = m; i < n; i++) {
        sCount[s[i]]++;
        sCount[s[i - m]]--;
        if (sCount[s[i - m]] == 0) {
            sCount.erase(s[i - m]);
        }
        if (isAnagram(sCount, pCount)) {
            result.push_back(i - m + 2);
        }
    }

    if (result.empty()) {
        cout << 0 << endl;
        cout << "none" << endl;
    } else {
        cout << result.size() << endl;
        for (int index : result) {
            cout << index << " ";
        }
        cout << endl;
    }

    return 0;
}
