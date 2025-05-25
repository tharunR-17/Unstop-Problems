#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, K, M;
    cin >> N >> K >> M;
    
    string S;
    cin >> S;
    
    // Read portal positions
    vector<int> portals(K);
    unordered_set<int> portalSet;
    for (int i = 0; i < K; i++) {
        cin >> portals[i];
        portals[i]--; // Convert to 0-based
        portalSet.insert(portals[i]);
    }
    
    // Early exit check
    if (M == 0 || K == 0) {
        cout << S << endl;
        return 0;
    }
    
    string result = S;
    int teleports = 0;
    
    // Process positions from left to right
    for (int i = 0; i < N && teleports < M; i++) {
        // Skip if not a portal
        if (portalSet.find(i) == portalSet.end()) {
            continue;
        }
        
        // Find the best character to place at position i
        int bestPos = -1;
        char bestChar = result[i];
        
        // Directly search through all portals (efficient for this problem size)
        for (int j = i + 1; j < N; j++) {
            if (portalSet.find(j) != portalSet.end() && result[j] > bestChar) {
                bestChar = result[j];
                bestPos = j;
            }
        }
        
        // If we found a better character, swap it
        if (bestPos != -1) {
            swap(result[i], result[bestPos]);
            teleports++;
        }
    }
    
    cout << result << endl;
    return 0;
}
