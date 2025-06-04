#include <iostream>
#include <vector>
#include <utility> // for std::pair
#include <bits/stdc++.h>
using namespace std;
// Function prototype
int min_rooms(std::vector<std::pair<int, int>>& jobs);

int main() {
    int N;
    std::cin >> N;
    
    std::vector<std::pair<int, int>> jobs(N);
    for (int i = 0; i < N; ++i) {
        int start, end;
        std::cin >> start >> end;
        jobs[i] = std::make_pair(start, end);
    }
    
    // Call the user logic function and print the output
    int result = min_rooms(jobs);
    std::cout << result << std::endl;
    
    return 0;
}

int min_rooms(std::vector<std::pair<int, int>>& jobs) {
    // User should implement their logic here

    sort(jobs.begin(),jobs.end());
   // Min-heap for keeping track of job end times
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // Push end time of the first job
    minHeap.push(jobs[0].second);

    for (int i = 1; i < jobs.size(); ++i) {
        // If the room is free (job starts after the earliest ending job)
        if (jobs[i].first >= minHeap.top()) {
            minHeap.pop();  // Free up the room
        }
        minHeap.push(jobs[i].second);  // Allocate room (new or reused)
    }

    // Number of rooms required is the max number of concurrent jobs
    return minHeap.size();

}
