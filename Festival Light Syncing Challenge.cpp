#include <iostream>
#include <vector>
#include <string>

using namespace std;

int findGrandSyncDay(const vector<string>& patterns, int N, int D) {
    vector<int> dayOnCounts(D, 0);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < D; ++j) {
            if (patterns[i][j] == '1') {
                dayOnCounts[j]++;
            }
        }
    }

    int maxOnCount = -1;
    int grandSyncDay = 1; 

    for (int j = 0; j < D; ++j) {
        if (dayOnCounts[j] > maxOnCount) {
            maxOnCount = dayOnCounts[j];
            grandSyncDay = j + 1;
        }
    }

    return grandSyncDay;
}

int main() {
    int N, D;
    cin >> N >> D;
    cin.ignore(); 

    vector<string> patterns(N);
    for (int i = 0; i < N; ++i) {
        getline(cin, patterns[i]);
    }

    int result = findGrandSyncDay(patterns, N, D);
    
    cout << result << endl;

    return 0;
}
