#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int Q;
    cin >> Q;

    vector<int> st;
    vector<int> freq(1000001, 0);
    int distinct = 0;

    while (Q--) {
        char op;
        cin >> op;

        if (op == '+') {
            int g;
            cin >> g;

            st.push_back(g);

            if (freq[g] == 0) {
                distinct++;
            }
            freq[g]++;
        }
        else if (op == '-') {
            int g = st.back();
            st.pop_back();

            freq[g]--;

            if (freq[g] == 0) {
                distinct--;
            }
        }
        else if (op == '?') {
            int top = st.empty() ? 0 : st.back();
            cout << top << ' ' << distinct << '\n';
        }
    }

    return 0;
}
