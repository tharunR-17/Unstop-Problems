#include <bits/stdc++.h>
using namespace std;

struct State {
    int holding;        // 0 or 1
    int buyPrice;       // valid only if holding == 1
    int cooldown;       // days left before next buy allowed
    int streak;         // 0, 1, 2 (3 triggers bonus and resets)
};

struct StateHash {
    size_t operator()(State const& s) const {
        return ((s.holding * 1000003ULL + s.buyPrice) * 1315423911ULL
               + s.cooldown * 31ULL + s.streak);
    }
};

struct StateEq {
    bool operator()(State const& a, State const& b) const {
        return a.holding == b.holding &&
               a.buyPrice == b.buyPrice &&
               a.cooldown == b.cooldown &&
               a.streak == b.streak;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> prices(n);
    for (int i = 0; i < n; i++) cin >> prices[i];
    int threshold;
    cin >> threshold;

    unordered_map<State, int, StateHash, StateEq> dp, nextDp;

    // Initial state
    dp[{0, 0, 0, 0}] = 0;

    for (int day = 0; day < n; day++) {
        nextDp.clear();

        for (auto &it : dp) {
            State s = it.first;
            int profitSoFar = it.second;

            // WAIT
            State waitState = s;
            if (waitState.cooldown > 0)
                waitState.cooldown--;
            nextDp[waitState] = max(nextDp[waitState], profitSoFar);

            // BUY
            if (s.holding == 0 && s.cooldown == 0) {
                State buyState;
                buyState.holding = 1;
                buyState.buyPrice = prices[day];
                buyState.cooldown = 0;
                buyState.streak = s.streak;
                nextDp[buyState] = max(nextDp[buyState], profitSoFar);
            }

            // SELL
            if (s.holding == 1) {
                int tradeProfit = prices[day] - s.buyPrice;
                int newProfit = profitSoFar + tradeProfit;

                State sellState;
                sellState.holding = 0;
                sellState.buyPrice = 0;

                if (tradeProfit > 0) {
                    int newStreak = s.streak + 1;
                    if (newStreak == 3) {
                        int bonus = (int)floor(tradeProfit * 0.10);
                        newProfit += bonus;
                        sellState.streak = 0;
                    } else {
                        sellState.streak = newStreak;
                    }
                    sellState.cooldown = tradeProfit / threshold;
                } else {
                    sellState.streak = 0;
                    sellState.cooldown = 0;
                }

                nextDp[sellState] = max(nextDp[sellState], newProfit);
            }
        }

        dp.swap(nextDp);
    }

    int ans = 0;
    for (auto &it : dp)
        ans = max(ans, it.second);

    cout << ans << "\n";
    return 0;
}
