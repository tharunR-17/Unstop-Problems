#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function prototype
int minimum_excess(int N, int K, vector<int>& students, vector<int>& packets);

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> students(N);
    vector<int> packets(K);
    for (int i = 0; i < N; i++) {
        cin >> students[i];
    }
    for (int i = 0; i < K; i++) {
        cin >> packets[i];
    }
    int result = minimum_excess(N, K, students, packets);
    cout << result << endl;
    return 0;
}

int minimum_excess(int N, int K, vector<int>& students, vector<int>& packets) {
    // Implement your logic here
    sort(students.begin(), students.end());
    sort(packets.begin(), packets.end());

    int total_excess = 0;
    int j = 0;

    for (int i = 0; i < N; i++) {
        while (j < K && packets[j] < students[i]) j++;
        if (j >= K) return -1;
        total_excess += packets[j] - students[i];
        j++;
    }

    return total_excess;
}
