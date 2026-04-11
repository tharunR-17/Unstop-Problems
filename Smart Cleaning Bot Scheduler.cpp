#include <iostream>
#include <vector>

using namespace std;

// Placeholder function for user logic
int maxRoomsCleaned(int N, int E, vector<int>& dirtLevels) {
    /**
     * Write your logic here.
     * Parameters:
     *   N (int): Number of rooms
     *   E (int): Total energy available
     *   dirtLevels (vector<int>): Dirt levels of each room
     * Returns:
     *   int: Maximum number of rooms cleaned
     */

     int sum = 0, maxDistance = 0;
     for(int i = 0; i < N; i++){
        if(i == 0){
            sum += dirtLevels[i];
        } else{
            sum = sum + dirtLevels[i] + 2;
        }
        if(sum <= E){
            maxDistance = i+1;
        } else{
            break;
        }
     }
    return maxDistance; // Placeholder return
}

int main() {
    int N, E;
    cin >> N >> E;

    vector<int> dirtLevels(N);
    for (int i = 0; i < N; ++i) {
        cin >> dirtLevels[i];
    }

    // Call user logic function and print the output
    int result = maxRoomsCleaned(N, E, dirtLevels);
    cout << result << endl;

    return 0;
}
