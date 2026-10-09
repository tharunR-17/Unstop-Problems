#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>

using namespace std;

vector<pair<int, int>> maxSlidewithfreq(vector<int>& pedest,int n,int W){

    deque<int> dq;
    unordered_map<int, int> freq;
    vector<pair<int, int>> ans;


    for(int i =0;i<n;i++){
        
        // remove element from front that are excluded from window
        while(!dq.empty() && dq.front() <= i - W){
            dq.pop_front();
        }
        
        // maintain decreasing order in deque
        while(!dq.empty() && pedest[dq.back()] < pedest[i]){
            dq.pop_back();
        }

        dq.push_back(i);
        freq[pedest[i]]++;

        if (i >= W) {
            freq[pedest[i - W]]--;
    
            if (freq[pedest[i - W]] == 0) {
                 freq.erase(pedest[i - W]);
            }
        }

        if (i >= W - 1) {
            int maximum = pedest[dq.front()];
            ans.push_back({maximum, freq[maximum]});
        }
    }

        return ans;

}



int main(){
    int n,W;
    cin>>n>>W;

    vector<int>pedest(n);

    for(int i =0;i<n;i++){
        cin>>pedest[i];
    }

    vector<pair<int, int>> ans = maxSlidewithfreq(pedest,n,W);
    for(auto i : ans){
        cout<<i.first<<" "<<i.second<<endl;
    }

return 0;
}
