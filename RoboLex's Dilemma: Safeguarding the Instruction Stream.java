#include <iostream>
#include <string>
using namespace std;

int user_logic(int n, string s) {
    // Write your logic here.
    int count = 0, idx = 0;
    while(idx + 3 <= n){
        if(s[idx] == 'k' && s[idx+1] == 'i' && s[idx+2] == 'l' && s[idx+3] == 'l'){
            count++;
            idx += 3;
        }
        idx++;
    }
    return n - count;
}

int main() {
    int n;
    string s;
    cin >> n >> s;
    int result = user_logic(n, s);
    cout << result << endl;
    return 0;
}
