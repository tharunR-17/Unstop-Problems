#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm> // Include this for max_element

// Function to extract numbers from the input string
std::vector<int> extractNumbers(const std::string &s) {
    std::vector<int> numbers;
    std::string temp = "";
    for (char ch : s) {
        if (isdigit(ch)) {
            temp += ch;
        } else {
            if (!temp.empty()) {
                numbers.push_back(std::stoi(temp));
                temp = "";
            }
        }
    }
    if (!temp.empty()) {
        numbers.push_back(std::stoi(temp));
    }
    return numbers;
}

// Function to generate Fibonacci numbers up to a given maximum
std::set<int> generateFibonacci(int maxNum) {
    std::set<int> fibonacci;
    int a = 0, b = 1;
    fibonacci.insert(a);
    fibonacci.insert(b);
    while (b <= maxNum) {
        int next = a + b;
        fibonacci.insert(next);
        a = b;
        b = next;
    }
    return fibonacci;
}

// Function to generate the first K Fibonacci numbers
std::vector<int> firstKFibonacci(int k) {
    std::vector<int> fibs;
    int a = 0, b = 1;
    fibs.push_back(a);
    if (k > 1) fibs.push_back(b);
    for (int i = 2; i < k; ++i) {
        int next = a + b;
        fibs.push_back(next);
        a = b;
        b = next;
    }
    return fibs;
}

// Function to solve the problem
std::string optimal_fibonacci_count(const std::string& s) {
    // Step 1: Extract numbers from the string
    std::vector<int> extractedNumbers = extractNumbers(s);

    // Step 2: Generate Fibonacci numbers up to the maximum extracted number
    int maxNum = *std::max_element(extractedNumbers.begin(), extractedNumbers.end());
    std::set<int> fibonacciSet = generateFibonacci(maxNum);

    // Step 3: Identify Fibonacci numbers in the extracted numbers
    std::vector<int> foundFibonacci;
    for (int num : extractedNumbers) {
        if (fibonacciSet.count(num)) {
            foundFibonacci.push_back(num);
        }
    }

    // Step 4: Prepare the output
    std::ostringstream result;
    if (foundFibonacci.empty()) {
        result << 0;
    } else {
        // Print count of Fibonacci numbers
        result << foundFibonacci.size() << "\n";

        // Print the Fibonacci numbers found
        for (int num : foundFibonacci) {
            result << num << " ";
        }
        result << "\n";

        // Print the first K Fibonacci numbers
        std::vector<int> firstK = firstKFibonacci(foundFibonacci.size());
        for (int num : firstK) {
            result << num << " ";
        }
    }
    return result.str();
}

int main() {
    std::string s;
    std::getline(std::cin, s);
    std::cout << optimal_fibonacci_count(s) << std::endl;
    return 0;
}
