#include <iostream>
#include <vector>

using namespace std;

long long user_logic(int n, vector<long long>& capacity, vector<long long>& load) {
    // User should implement the logic here
    long long totalCapacity = 0, totalLoad = 0;
    for (int i = 0; i < n; i++) {
        totalCapacity += capacity[i];
        totalLoad += load[i];
    }
    if (totalLoad > totalCapacity) return -1;

    long long totalOverload = 0;
    for (int i = 0; i < n; i++) {
        if (load[i] > capacity[i]) {
            totalOverload += load[i] - capacity[i];
        }
    }
    return totalOverload; // Placeholder return value
}

int main() {
    int n;
    cin >> n;
    vector<long long> capacity(n);
    vector<long long> load(n);

    for (int i = 0; i < n; ++i) {
        cin >> capacity[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> load[i];
    }

    long long result = user_logic(n, capacity, load);
    cout << result << endl;

    return 0;
}
