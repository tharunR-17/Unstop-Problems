#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cmath>


int find_longest_distinct_substring(int N, int D, const std::string& S) {
    int maxLength = -1;

    for (int i = 0; i < N; ++i) {
        std::unordered_set<char> seen;
        for (int j = i; j < N; ++j) {
            if (seen.count(S[j])) break; // Duplicate found, stop expanding
            seen.insert(S[j]);
            if (std::abs(S[i] - S[j]) == D) {
                int len = j - i + 1;
                if (len > maxLength)
                    maxLength = len;
            }
        }
    }

    return maxLength == -1 ? -1 : maxLength;
}

int main() {
    int N, D;
    std::string S;
    std::cin >> N >> D >> S;
    int result = find_longest_distinct_substring(N, D, S);
    std::cout << result << std::endl;
    return 0;
}
