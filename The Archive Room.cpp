#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    int N;
    cin >> N;

    stack<long long> st;

    while (N--) {
        string op;
        cin >> op;

        if (op == "ADD") {
            long long x;
            cin >> x;
            st.push(x);
        } else {
            if (!st.empty())
                st.pop();
        }
    }

    if (st.empty())
        cout << -1;
    else
        cout << st.top();

    return 0;
}
