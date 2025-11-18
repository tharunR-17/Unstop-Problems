#include <iostream>
#include <string>
using namespace std;

string waveform_transform(const string &s) {
    int n = s.length();
    string result(n, ' ');   

    int mid = n / 2;       
    int left = mid;
    int right = mid;

    result[mid] = s[0];      
    for (int i = 1; i < n; i++) {
        if (i % 2 == 1) {
           
            left--;
            result[left] = s[i];
        } else {
            
            right++;
            result[right] = s[i];
        }
    }

    return result;
}

int main() {
    string S;
    getline(cin, S);

    string result = waveform_transform(S);
    cout << result << endl;

    return 0;
}
