#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
        int64_t d, k;
        cin >> d >> k;
        int64_t x = 0, y = 0;
        while(true) {
            if(x <= y && (x + k) * (x + k) + y * y <= d * d)
                x += k;
            else if(x > y && (y + k) * (y + k) + x * x <= d * d)
                y += k;
            else
                break;
        }
        if(x == y)
            cout << "Utkarsh" << endl;
        else
            cout << "Ashish" << endl;
    
    return 0;
}
