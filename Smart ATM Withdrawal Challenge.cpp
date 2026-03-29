#include <iostream>
#include <vector>

using namespace std;

// Placeholder for user logic
int calculateMinimumNotes(int amount, vector<int> &available) {
    // User will implement this function
    // Parameters:
    //   amount: Integer representing the amount to withdraw
    //   available: Vector of integers representing the availability of notes (₹2000, ₹500, ₹200, ₹100, ₹50, ₹20, ₹10)
    // Return:
    //   Integer representing the minimum number of notes required or -1 if not possible
    vector<int> values = {2000, 500, 200, 100, 50, 20, 10};
    int ans = 0;
    for(int i=0;i<7;i++){
        ans += min(amount/values[i], available[i]);
        amount -= min(amount/values[i], available[i])*values[i];
    }
    if(amount > 0)return -1; // Placeholder return
    return ans;
}

int main() {
    int amount;
    vector<int> available(7);
    
    // Read the amount to withdraw
    cin >> amount;
    
    // Read the availability of each denomination
    for (int i = 0; i < 7; ++i) {
        cin >> available[i];
    }
    
    // Call the user logic function
    int result = calculateMinimumNotes(amount, available);
    
    // Print the result
    cout << result << endl;
    
    return 0;
}
