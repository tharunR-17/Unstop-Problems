#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int median_sum(vector<int> arr) {
    long long sum_of_medians = 0;

    while (!arr.empty()) {
        sort(arr.begin(), arr.end());
        int n = arr.size();

        if (n == 1) {
            sum_of_medians += arr[0];
            arr.pop_back();
            break;
        }

        if (n % 2 == 1) {
            int median = arr[n / 2];
            arr.erase(arr.begin() + n / 2);
            sum_of_medians += median;
        } else {
            int mid1 = arr[n / 2 - 1];
            int mid2 = arr[n / 2];
            int median = (mid1 + mid2) / 2;
            arr.erase(arr.begin() + n / 2 - 1);
            sum_of_medians += median;
        }
    }

    return sum_of_medians;
}

int main() {
    int N;
    cin >> N;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    cout << median_sum(arr) << endl;

    return 0;
}
