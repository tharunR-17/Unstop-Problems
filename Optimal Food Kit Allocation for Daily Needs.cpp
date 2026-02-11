#include <iostream>
#include <vector>
#include<bits/stdc++.h>
using namespace std;

// Placeholder function for user logic
int max_people_with_calories(vector<int>& needs, vector<int>& kits) {
    /*
    Write your logic here.
    Parameters:
        needs (vector<int>): Calorie requirements of each person
        kits (vector<int>): Calorie value of each food kit
    Returns:
        int: Maximum number of people whose calorie needs can be met
    */
    int cnt=0;
    int i=0;
    int j=0;
    sort(needs.begin(),needs.end());
    sort(kits.begin(),kits.end());
    while(i<needs.size() && j<kits.size()){
        if(kits[j]>=needs[i]){
            cnt++;
            i++;
            j++;
        }else{
            j++;
        }
    }
    return cnt; // Placeholder return statement
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> needs(N);
    vector<int> kits(M);

    for (int i = 0; i < N; ++i) {
        cin >> needs[i];
    }

    for (int i = 0; i < M; ++i) {
        cin >> kits[i];
    }

    // Call user logic function and print the output
    int result = max_people_with_calories(needs, kits);
    cout << result << endl;

    return 0;
}
