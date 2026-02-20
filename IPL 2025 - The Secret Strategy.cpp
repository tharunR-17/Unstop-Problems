#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Helper function to check for primality
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    int sqrtN = sqrt(n);
    for (int i = 3; i <= sqrtN; i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}

// Function to encrypt the message
string encryptMessage(const vector<int>& arr) {
    string result = "";
    for (size_t i = 0; i < arr.size(); ++i) {
        if (isPrime(arr[i]))
            result += "*";
        else
            result += to_string(arr[i]);
        if (i != arr.size() - 1)
            result += " ";
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<int> arr(N);

    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    string result = encryptMessage(arr);
    cout << result << "\n";

    return 0;
}
