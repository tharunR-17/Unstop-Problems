#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>

int shortest_substring_length(const std::string &S, const std::string &L) {
    std::unordered_map<char, int> required, window;
    for (char c : L) {
        required[c]++;
    }

    int have = 0, need = required.size();
    int left = 0;
    int minLen = INT_MAX;

    for (int right = 0; right < S.length(); ++right) {
        char c = S[right];
        window[c]++;

        // Count matched characters
        if (required.count(c) && window[c] == required[c]) {
            have++;
        }

        // Try to shrink the window
        while (have == need) {
            // Update minimum length
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
            }

            char leftChar = S[left];
            window[leftChar]--;
            if (required.count(leftChar) && window[leftChar] < required[leftChar]) {
                have--;
            }
            left++;
        }
    }

    return minLen == INT_MAX ? -1 : minLen;
}

int main() {
    std::string S;
    std::string L;

    std::getline(std::cin, S);
    std::getline(std::cin, L);

    int result = shortest_substring_length(S, L);
    std::cout << result << std::endl;

    return 0;
}
