#include <iostream>
#include <vector>
using namespace std;

int countOne(int n){
    int count = 0;
    while(n > 0){
        int rem = n % 2;
        if(rem == 1){
            count++;
        }
        n /= 2;
    }

    return count;
}

// Placeholder function where user will write their logic
vector<int> user_logic(int N) {
    // User logic here
    // Return a vector of integers representing the running totals
    vector<int> result;
    int sum = 0;
    for(int i=0; i<=N; i++){
        int onesCount = countOne(i);

        if(i % 2 == 0){
            sum = sum + onesCount; 
        }else{
            sum = sum - onesCount;
        }

        result.push_back(sum);
    }

    return result;
}

int main() {
    int N;
    cin >> N; // Input the number N

    // Call user logic function
    vector<int> result = user_logic(N);

    // Print the output in the required format
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
