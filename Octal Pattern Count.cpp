#include <iostream>
using namespace std;

string user_logic(int N);

int main() {
    int N;
    cin >> N;
    string result = user_logic(N);
    cout << result << endl;
    return 0;
}

string user_logic(int N) {
    if (N == 0) return "1";
    
    const long long MOD = 1e9 + 7;
    
    long long a = 1, e = 1, i = 1, o = 1, u = 1;
    
    for (int step = 1; step < N; step++) {
        long long na = (e + u) % MOD;
        long long ne = (i + a) % MOD;
        long long ni = (o + e) % MOD;
        long long no_ = (u + i) % MOD;
        long long nu = (a + o) % MOD;
        a = na; e = ne; i = ni; o = no_; u = nu;
    }
    
    long long total = (a + e + i + o + u) % MOD;
    
    if (total == 0) return "1";
    
    string octal = "";
    long long tmp = total;
    while (tmp > 0) {
        octal = char('0' + (tmp % 8)) + octal;
        tmp /= 8;
    }
    
    return octal;
}
