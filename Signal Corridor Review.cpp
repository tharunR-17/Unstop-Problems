#include <iostream>
#include <vector>
#include <deque>
#include <map>

using namespace std;

int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    if (!(cin >> n >> k)) return 0;
    
    vector<int> brightness(n);
    for(int i = 0; i < n; i++) {
        cin >> brightness[i];
    }
    
    deque<int> dq; // Stores indices, not the actual values
    vector<int> max_vals;
    
    // 1. Sliding Window using Monotonic Deque
    for(int i = 0; i < n; i++) {
        // Remove indices that are out of the current window of size k
        if (!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }
        
        // Remove elements from the back that are smaller than or equal to the new element
        while (!dq.empty() && brightness[dq.back()] <= brightness[i]) {
            dq.pop_back();
        }
        
        // Insert the current index
        dq.push_back(i);
        
        // If our window has reached size k, record the maximum (at the front of deque)
        if (i >= k - 1) {
            max_vals.push_back(brightness[dq.front()]);
        }
    }
    
    // 2. Frequency counting and dominant value logic
    map<int, int> freq;
    for (int i = 0; i < max_vals.size(); i++) {
        freq[max_vals[i]]++;
        cout << max_vals[i] << (i == max_vals.size() - 1 ? "" : " ");
    }
    cout << "\n";
    
    int dominant_val = -1;
    int max_count = -1;
    
    // std::map sorts by key ascending. 
    // Using '>' ensures we only overwrite if the count is strictly higher, 
    // preserving the smallest value in case of a tie.
    for (auto const& [val, count] : freq) {
        if (count > max_count) {
            max_count = count;
            dominant_val = val;
        }
    }
    
    cout << dominant_val << " " << max_count << "\n";
    
    return 0;
}
