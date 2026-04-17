#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

// Define a structure to store refund requests
struct RefundRequest {
    int refund;
    int priority;
    int timestamp;
};

// User logic function
pair<long, long> calculateMaximumPriorityAndRefund(int N, int K, vector<RefundRequest> &requests) {
    // User should implement the logic here to calculate the maximum total priority score
    // and the maximum total refund amount by selecting K refund requests.
    // This is a placeholder function.
    sort(requests.begin(), requests.end(), [](const RefundRequest &a, const RefundRequest &b) {
        if (a.priority != b.priority) return a.priority > b.priority;
        return a.refund > b.refund;
    });

    long totalPriority = 0, totalRefund = 0;
    for (int i = 0; i < K; i++) {
        totalPriority += requests[i].priority;
        totalRefund += requests[i].refund;
    }

    return make_pair(totalPriority, totalRefund); // Placeholder return
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<RefundRequest> requests(N);

    for (int i = 0; i < N; ++i) {
        cin >> requests[i].refund >> requests[i].priority >> requests[i].timestamp;
    }

    // Call user logic function
    pair<long, long> result = calculateMaximumPriorityAndRefund(N, K, requests);

    // Print the result
    cout << result.first << " " << result.second << endl;

    return 0;
}
