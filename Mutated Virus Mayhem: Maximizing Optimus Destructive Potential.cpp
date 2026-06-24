#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int maxMutatedViruses(int N, vector<int>& contamination_levels) {
    unordered_map<int, int> freq;
    
    // Count the frequency of each contamination level
    for (int level : contamination_levels) {
        freq[level]++;
    }

    int mutatedVirusCount = 0;

    // Sort keys to handle consecutive levels
    vector<int> levels;
    for (const auto& entry : freq) {
        levels.push_back(entry.first);
    }
    sort(levels.begin(), levels.end());

    // Iterate through each level to form groups
    for (size_t i = 0; i < levels.size(); ++i) {
        int level = levels[i];
        while (freq[level] >= 3) {
            // Form a group of three identical contamination levels
            mutatedVirusCount++;
            freq[level] -= 3;
        }
        // Check for consecutive triplets if possible
        if (i + 2 < levels.size() && levels[i + 1] == level + 1 && levels[i + 2] == level + 2) {
            while (freq[level] > 0 && freq[level + 1] > 0 && freq[level + 2] > 0) {
                // Form a group with consecutive levels
                mutatedVirusCount++;
                freq[level]--;
                freq[level + 1]--;
                freq[level + 2]--;
            }
        }
    }

    return mutatedVirusCount;
}

int main() {
    int N;
    cin >> N;
    vector<int> contamination_levels(N);
    for (int i = 0; i < N; i++) {
        cin >> contamination_levels[i];
    }
    
    int result = maxMutatedViruses(N, contamination_levels);
    cout << result << endl;

    return 0;
}
