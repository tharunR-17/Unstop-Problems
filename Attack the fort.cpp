#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdlib> // For std::abs

using namespace std;

void calculate_difference(vector<int>& arr) {
    // Filter out forts with power less than or equal to 0
    vector<int> filtered_forts;
    for (int power : arr) {
        if (power > 0) {
            filtered_forts.push_back(power);
        }
    }
    
    if (filtered_forts.empty()) {
        cout << -1 << endl;
        exit(0);
    }
    
    // Sort the filtered forts in increasing order
    sort(filtered_forts.begin(), filtered_forts.end());
    
    int max_length_sequence = 0;
    int current_length = 0;
    int last_attacked = -1;
    int final_last_attacked = -1;
    
    for (int power : filtered_forts) {
        if (last_attacked == -1 || power - last_attacked == 1) {
            current_length++;
            last_attacked = power;
        } else {
            current_length = 1;
            last_attacked = power;
        }
        
        if (current_length > max_length_sequence) {
            max_length_sequence = current_length;
            final_last_attacked = last_attacked;
        }
    }
    
    int max_power = filtered_forts.back();
    int difference = abs(final_last_attacked + 1 - max_power);
    
    cout << difference << endl;
}

int main() {
    int n;
    cin >> n;
    
    set<int> arr_set;
    for (int i = 0; i < n; ++i) {
        int power;
        cin >> power;
        arr_set.insert(power);
    }
    
    vector<int> arr(arr_set.begin(), arr_set.end());
    
    // Calculating the difference
    calculate_difference(arr);
    
    return 0;
}
