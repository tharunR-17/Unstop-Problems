#include <bits/stdc++.h>
using namespace std;

int calculateMinPatternChanges(int N, const string& S) {
    int result = INT_MAX, countL = 0, countS = 0;
    if(S[0] != 'l') 
        countL++;
    char ch = 'l';
    for(int i = 1; i < N; i++){
        if(S[i] == ch){
            if(ch == 'l')
                countS++;
            else
                countL++;
        }
        ch = (ch == 'l') ? 's' : 'l';
    }
    int count = min(countS, countL);
    countL -= count;
    countS -= count;
    result = min(result, countL + countS + count);

    countL = 0, countS = 0;
    if(S[0] != 's')
        countS++;
    ch = 's';
    for(int i = 1; i < N; i++){
        if(S[i] == ch){
            if(ch == 'l')
                countS++;
            else
                countL++;
        }
        ch = (ch == 'l') ? 's' : 'l';
    }
    count = min(countS, countL);
    countL -= count;
    countS -= count;
    result = min(result, countL + countS + count);
    return result;
}

int main() {
    int N;
    string S;
    cin >> N >> S;
    int result = calculateMinPatternChanges(N, S);
    cout << result << endl;
    return 0;
}
