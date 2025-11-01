#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

// Custom comparator for sorting
bool customSort(pair<char, pair<int, int>>& a, pair<char, pair<int, int>>& b) {
    if (a.second.first != b.second.first) // Sort by frequency in descending order
        return a.second.first > b.second.first;
    return a.second.second < b.second.second; // If frequency is the same, sort by the first appearance index
}

string sortByFrequency(string S) {
    unordered_map<char, pair<int, int>> frequencyMap; // {char : {frequency, first appearance index}}
    for (int i = 0; i < S.length(); i++) {
        if (frequencyMap.find(S[i]) == frequencyMap.end())
            frequencyMap[S[i]] = {0, i}; // Initialize frequency and index
        frequencyMap[S[i]].first++; // Increment frequency
    }

    vector<pair<char, pair<int, int>>> freqVector(frequencyMap.begin(), frequencyMap.end());

    // Sort based on custom criteria
    sort(freqVector.begin(), freqVector.end(), customSort);

    // Construct the result string
    string result = "";
    for (auto& elem : freqVector) {
        result += string(elem.second.first, elem.first);
    }

    return result;
}

int main() {
    string S;
    cin >> S;
    cout << sortByFrequency(S) << endl;
    return 0;
}
