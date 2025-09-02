#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

long long user_logic(long long n) {
    // Write your logic here
    // Ensure you return the correct value based on the problem statement
    return (n%mod+mod)%mod; // Placeholder return value
}

int main() {
    long long n;
    cin >> n;
    
    // Call user logic function
    long long result = user_logic(n);
    
    // Output the result
    cout << result << endl;
    
    return 0;
}
