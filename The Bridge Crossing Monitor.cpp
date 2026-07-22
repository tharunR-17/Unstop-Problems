#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;

    queue<int> q;

    for (int i = 0; i < n; i++) {
        string op;
        cin >> op;

        if (op == "ENTER") {
            int x;
            cin >> x;
            q.push(x);
        } else { 
            if (!q.empty()) {
                q.pop();
            }
        }
    }

    if (q.empty()) {
        cout << "EMPTY";
    } else {
        cout << q.front();
    }

    return 0;
}
