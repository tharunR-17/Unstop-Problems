#include <iostream>
#include <string>
#include <stack>

int main() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    std::stack<char> result;

    for (char c : s) {
        if (c == '_') {
            if (!result.empty()) {
                result.pop(); // Remove the character before '_'
            }
        } else {
            result.push(c);
        }
    }

    // Construct the final string from the stack
    std::string finalString = "";
    while (!result.empty()) {
        finalString = result.top() + finalString;
        result.pop();
    }

    if (finalString.empty()) {
        std::cout << "-1" << std::endl;
    } else {
        std::cout << finalString << std::endl;
    }

    return 0;
}
