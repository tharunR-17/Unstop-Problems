#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
int dp[3003][3003];

int main(){
    int N, K; cin >> N >> K;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= K; j++){
            if(i == 1 && j == 1){
                dp[i][j] = 1;
                continue;
            }
            dp[i][j] = (dp[i-1][j-1] * 1ll * (i - 2 * (j - 1)) ) % mod;
            dp[i][j] = (dp[i][j] + 0ll + dp[i-1][j] * 2 * 1ll * j) % mod;
        }
    }
    int ans = 0;
    for(int i = 1; i <= K; i++) ans = (ans + 0ll + dp[N][i]) % mod;
    cout << ans << endl;
    return 0;
}
