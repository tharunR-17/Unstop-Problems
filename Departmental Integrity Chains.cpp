#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

struct Student {
    int roll;
    int dept;
    int loyalty;
    
    bool operator<(const Student& other) const {
        return loyalty < other.loyalty;
    }
};

int calculateIntegrityChains(vector<Student>& students, int N, int D) {
    sort(students.begin(), students.end());

    vector<bool> used(N, false);

    int chains = 0;

    while (true) {
        unordered_set<int> usedDepts;
        vector<int> chainIndexes;
        bool hasCS = false;
        int lastLoyalty = -1;

        for (int i = 0; i < N; ++i) {
            if (used[i]) continue;
            Student& s = students[i]; 

            if (s.loyalty > lastLoyalty && usedDepts.find(s.dept) == usedDepts.end()) {
                chainIndexes.push_back(i);
                usedDepts.insert(s.dept);
                lastLoyalty = s.loyalty;
                if (s.dept == 1) hasCS = true;
            }
        }

        if (chainIndexes.size() >= 2 && hasCS) {
            for (int idx : chainIndexes) {
                used[idx] = true;
            }
            chains++;
        } else {
            break; 
        }
    }

    return chains;
}

int main() {
    int N, D;
    cin >> N >> D;

    vector<Student> students(N);
    for (int i = 0; i < N; ++i) {
        cin >> students[i].roll >> students[i].dept >> students[i].loyalty;
    }

    int result = calculateIntegrityChains(students, N, D);
    cout << result << endl;

    return 0;
}
