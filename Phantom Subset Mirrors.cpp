#include <iostream>
#include <vector>

using namespace std;

// Placeholder function where the user will write their logic
int countPhantomSubsets(const vector<int>& A) {
    // User will write their logic here
    int c=0;
    int n=A.size();
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(A[i]<A[j])c++;
        }
    }
    return c;
    return 0;
}

int main() {
    // Input handling
    int n;
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    // Call user logic function and print the output
    int result = countPhantomSubsets(A);
    cout << result << endl;

    return 0;
}
