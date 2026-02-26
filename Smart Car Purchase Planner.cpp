#include <bits/stdc++.h>
using namespace std;

struct Car {
    int base;
    int emi;
    int time;
    int discount;
};

int calculate_max_base_cost(int N, int K, int M, const vector<Car>& cars) {

    int ans = -1;

    for (int i = 0; i < N; ++i) {
        
        long long upfront_cost = (long long)cars[i].base - cars[i].discount;
        long long emi_cost = (long long)cars[i].emi * cars[i].time;

        bool can_buy = false;

        if (upfront_cost <= K) {
            can_buy = true;
        }

        if (cars[i].time <= M && emi_cost <= K) {
            can_buy = true;
        }

        if (can_buy) {
            ans = max(ans, cars[i].base);
        }
    }

    return ans;
}

int main() {
    int N, K, M;
    cin >> N >> K >> M;

    vector<Car> cars(N);
    for (int i = 0; i < N; ++i) {
        cin >> cars[i].base >> cars[i].emi >> cars[i].time >> cars[i].discount;
    }

    int result = calculate_max_base_cost(N, K, M, cars);
    cout << result << endl;

    return 0;
}
