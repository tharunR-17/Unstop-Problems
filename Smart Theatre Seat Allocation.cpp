#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> calculateSeatStatus(int N, int Q, vector<int> K) {
    vector<int> seats(N, 0); 
    
    auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
        int lenA = a.second - a.first + 1;
        int lenB = b.second - b.first + 1;
        if (lenA != lenB) return lenA < lenB; 
        return a.first > b.first;            
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> freeBlocks(cmp);
    freeBlocks.push({0, N - 1}); 

    for (int i = 0; i < Q; ++i) {
        int groupSize = K[i];
        vector<pair<int, int>> tried;
        bool placed = false;

        while (!freeBlocks.empty()) {
            auto block = freeBlocks.top();
            freeBlocks.pop();

            int length = block.second - block.first + 1;

            if (length < groupSize) {
                tried.push_back(block); 
                continue;
            }

            int startPos;
            if (length == groupSize) {
                startPos = block.first;
            } else {
                int leftSpace = (length - groupSize) / 2;
                startPos = block.first + leftSpace;
            }

            for (int j = startPos; j < startPos + groupSize; ++j) {
                seats[j] = 1;
            }

            if (startPos > block.first) {
                freeBlocks.push({block.first, startPos - 1});
            }
            if (startPos + groupSize <= block.second) {
                freeBlocks.push({startPos + groupSize, block.second});
            }

            placed = true;
            break;
        }

        for (auto& b : tried) {
            freeBlocks.push(b);
        }
    }

    return seats;
}

int main() {
    int N, Q;
    cin >> N >> Q;

    vector<int> K(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> K[i];
    }

    vector<int> result = calculateSeatStatus(N, Q, K);

    for (int seat : result) {
        cout << seat << " ";
    }
    cout << endl;

    return 0;
}
