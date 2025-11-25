#include <iostream>
#include <string>
#include <vector>

using namespace std;

void rearrange_string(string& S, const string& T) {
    vector<int> count(26, 0);
    for (char c : S) {
        count[c - 'a']++;
    }

    string result = "";

    for (char c : T) {
        int idx = c - 'a';
        if (count[idx] > 0) {
            result.append(count[idx], c);
            count[idx] = 0; 
        }
    }

    for (char c : S) {
        int idx = c - 'a';
        if (count[idx] > 0) {
            result.append(count[idx], c);
            count[idx] = 0; 
        }
    }

    S = result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string S, T;
    if (cin >> S >> T) {
        rearrange_string(S, T);
        cout << S << endl;
    }
    return 0;
}
