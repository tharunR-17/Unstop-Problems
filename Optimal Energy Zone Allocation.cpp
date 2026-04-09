#include <iostream>
#include <vector>
using namespace std;

// Placeholder function where the user will write their logic
int countValidPartitions(vector<int>& E, int N) {
    // User logic goes here
    vector<int>pre(N);
    pre[0]=E[0];
    for(int i=1;i<N;i++){
        pre[i]=pre[i-1]+E[i];
    }
    int c=0;
    int l=0,r=N-1;
    int sum=0;
    while(r-l>1){
        sum=sum+E[l]+E[r];
        int x= pre[r-1]-pre[l];
        if(sum>x){
            c++;
        }
        l++;
        r--;
    }
    return c; // Placeholder return value
}

int main() {
    int N;
    cin >> N; // Read the number of plants

    vector<int> E(N);
    for (int i = 0; i < N; ++i) {
        cin >> E[i];
    }

    int result = countValidPartitions(E, N);

    cout << result << endl;

    return 0;
}
