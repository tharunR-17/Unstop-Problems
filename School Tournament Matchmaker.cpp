#include<bits/stdc++.h>
using namespace std;

// User logic function
pair<int, int> findWinnerAndRounds(int N, int K, vector<int>& skillLevels) {
    // Placeholder for user logic
    // Parameters:
    // N: Number of students
    // K: Maximum allowable skill difference
    // skillLevels: Vector containing the skill levels of the students
    // Return a pair of integers:
    // - First integer: Total number of rounds played
    // - Second integer: Skill level of the final winner (or -1 if no winner)
    if(N==1)return {0, skillLevels[0]};
    sort(skillLevels.begin(), skillLevels.end());
    vector<int> s;
    vector<bool> used(N, false);
    for(int i=1;i<N;i++){
        if(used[i-1]);
        else if(skillLevels[i]-skillLevels[i-1] <= K){
            used[i-1] = used[i] = true;
            s.push_back(skillLevels[i]);
        }
    }
    // cout<<s.size()<<" ";
    if(s.size()==0){
        return {0, -1};
    }
    pair<int, int> p = findWinnerAndRounds(s.size(), K, s);
    return {p.first+1, p.second};
     // Placeholder return
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> skillLevels(N);
    for (int i = 0; i < N; ++i) {
        cin >> skillLevels[i];
    }

    // Call the user logic function
    pair<int, int> result = findWinnerAndRounds(N, K, skillLevels);

    // Output the result
    cout << result.first << " " << result.second << endl;

    return 0;
}
