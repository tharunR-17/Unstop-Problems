#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Method to calculate the energy of a character
int getEnergy(char c) {
    if (isdigit(c)) {
        return 10 * (c - '0');  // Energy of a digit
    } else {
        return c - 'a' + 1;  // Energy of a letter (1-based index)
    }
}

// Method to simulate the collapse process
string collapseChain(const string& s) {
    // Use a stack to handle collapses
    stack<char> st;

    for (char c : s) {
        // If stack is not empty and top of the stack has the same energy as current character, collapse
        if (!st.empty() && getEnergy(st.top()) == getEnergy(c)) {
            st.pop();  // Remove the top element from the stack (collapse it)
        } else {
            st.push(c);  // Push the current character onto the stack
        }
    }

    // If the stack is empty, return -1 (indicating all characters have collapsed)
    if (st.empty()) {
        return "-1";
    }

    // Otherwise, reconstruct the string from the stack
    string result = "";
    while (!st.empty()) {
        result = st.top() + result;  // Build the final string from stack
        st.pop();
    }

    return result;
}

int main() {
    // Input the string S
    string s;
    cin >> s;

    // Process the chain and print the result
    cout << collapseChain(s) << endl;

    return 0;
}
