#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

bool is_peak(const vector<int>& arr, int i) {
    return i > 0 && i + 1 < arr.size() && arr[i] > arr[i - 1] && arr[i] > arr[i + 1];
}

set<int> count_peaks(const vector<int>& arr) {
    set<int> peaks;
    for (int i = 1; i + 1 < arr.size(); ++i) {
        if (is_peak(arr, i)) {
            peaks.insert(i);
        }
    }
    return peaks;
}

int local_peak_count(const vector<int>& arr, const set<int>& affected) {
    int count = 0;
    for (int i : affected) {
        if (is_peak(arr, i)) {
            ++count;
        }
    }
    return count;
}

int minimize_energy_peaks(vector<int>& arr) {
    int n = arr.size();
    set<int> original_peaks = count_peaks(arr);
    int min_peaks = original_peaks.size();

    set<int> candidate_set;
    for (int p : original_peaks) {
        for (int d = -2; d <= 2; ++d) {
            int idx = p + d;
            if (idx >= 0 && idx < n) {
                candidate_set.insert(idx);
            }
        }
    }

    vector<int> candidates(candidate_set.begin(), candidate_set.end());

    for (int i = 0; i < candidates.size(); ++i) {
        for (int j = i; j < candidates.size(); ++j) {
            int a = candidates[i], b = candidates[j];
            if (a == b) continue;

            swap(arr[a], arr[b]);


            set<int> affected;
            for (int idx : {a, b}) {
                for (int d = -2; d <= 2; ++d) {
                    int k = idx + d;
                    if (k >= 0 && k < n) {
                        affected.insert(k);
                    }
                }
            }


            int new_local = local_peak_count(arr, affected);
            int total = original_peaks.size();

            for (int idx : affected) {
                if (original_peaks.count(idx)) {
                    total--;
                }
            }

            total += new_local;
            min_peaks = min(min_peaks, total);

            swap(arr[a], arr[b]); 
        }
    }

    return min_peaks;
}

int main() {
    int n;
    cin>>n;
    vector<int> arr (n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    
    cout << minimize_energy_peaks(arr) << endl;
    return 0;
}
