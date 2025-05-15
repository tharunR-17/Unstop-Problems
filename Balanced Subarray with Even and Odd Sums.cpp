#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;

// Function to count number of 1s in binary representation
int countOnes(int num) {
    return __builtin_popcount(num);
}

int longestBalancedSubarray(vector<int>& arr) {
    int n = arr.size();
    vector<int> ones(n);

    for (int i = 0; i < n; ++i) {
        ones[i] = countOnes(arr[i]);
    }

    unordered_map<int, int> diffIndex;
    diffIndex[0] = -1;

    int even_sum = 0, odd_sum = 0, max_len = 0;

    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0)
            even_sum += ones[i];
        else
            odd_sum += ones[i];

        int diff = even_sum - odd_sum;

        if (diffIndex.find(diff) != diffIndex.end()) {
            max_len = max(max_len, i - diffIndex[diff]);
        } else {
            diffIndex[diff] = i;
        }
    }

    return max_len;
}

int main() {
    string line;
    getline(cin, line);  // Read the full line of input

    stringstream ss(line);
    vector<int> arr;
    int num;

    while (ss >> num) {
        arr.push_back(num);
    }

    int result = longestBalancedSubarray(arr);
    cout << result << endl;

    return 0;
}
