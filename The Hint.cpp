#include <iostream>
#include <string>

int LongestConsecutiveCharacter(const std::string& s) {
    // Write your logic here.
    // Parameters:
    //     s (const std::string&): The passcode string consisting of lowercase alphabets
    // Returns:
    //     int: Length of the longest part of the passcode that contains only one unique character
    int maxLen = 1, curLen = 1;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == s[i-1]) {
            curLen++;
            maxLen = std::max(maxLen, curLen);
        } else {
            curLen = 1;
        }
    }
    return maxLen;
}

int main() {
    std::string s;
    std::getline(std::cin, s);
    
    // Call user logic function and print the output
    int result = LongestConsecutiveCharacter(s);
    std::cout << result << std::endl;
    
    return 0;
}
