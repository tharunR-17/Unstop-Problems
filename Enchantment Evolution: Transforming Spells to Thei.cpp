#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, t;
    cin >> n >> t;

    string s;
    cin >> s;

    while (t--) {
        if (!next_permutation(s.begin(), s.end())) {
            cout << "FAIL" << endl;
            return 0;
        }
    }

    cout << s << endl;
    return 0;
}
