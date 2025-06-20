#include <bits/stdc++.h>
using namespace std;

bool checkVowel(char ch) {
    return ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' || ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

bool checkPrime(int num) {
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}

void evaluateWord(const string &word) {
    int vowelCount = 0, consonantCount = 0;
    for (auto ele : word) {
        if (checkVowel(ele)) {
            vowelCount++;
        } else {
            consonantCount++;
        }
    }
    if (vowelCount < 2)
        cout << "Disqualify" << endl;
    else {
        int root = sqrt(consonantCount);
        if (root * root != consonantCount)
            cout << "Disqualify" << endl;
        else {
            if (checkPrime(root))
                cout << "Qualify" << endl;
            else
                cout << "Disqualify" << endl;
        }
    }
}

int main() {
    string word;
    getline(cin, word);
    evaluateWord(word);
    return 0;
}
