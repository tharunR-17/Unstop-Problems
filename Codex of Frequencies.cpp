#include <bits/stdc++.h>
using namespace std;

bool comparePairs(pair<int, char> p1, pair<int, char> p2) {
    if (p1.first != p2.first) {
        return p1.first > p2.first;
    }
    return p1.second < p2.second;
}

void processString(const string& input) {
    vector<pair<int, char>> frequency(26, {0, 'a'});
    vector<pair<int, char>> oddFrequencies;
    
    for (int i = 0; i < 26; i++) {
        frequency[i].second += i;
    }
    
    for (char c : input) {
        frequency[c - 'a'].first++;
    }
    
    sort(frequency.begin(), frequency.end(), comparePairs);
    
    long long product = 1;
    int count = 0;
    
    for (const auto& item : frequency) {
        if (item.first % 2 == 1) {
            oddFrequencies.push_back(item);
            product *= item.first;
            count++;
        }
        if (count == 3) {
            break;
        }
    }
    
    if (count == 3) {
        for (int i = 0; i < 3; i++) {
            cout << oddFrequencies[i].second << " " << oddFrequencies[i].first << endl;
        }
        cout << product << endl;
    } else if (count > 0) {
        cout << oddFrequencies[0].second << " " << oddFrequencies[0].first << endl;
    } else {
        cout << -1 << endl;
    }
}

int main() {
    string input;
    getline(cin, input);
    processString(input);
    return 0;
}
