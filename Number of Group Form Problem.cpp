#include<bits/stdc++.h>

using namespace std;

bool sim(const string& a, const string& b) {
    int x=0;
    for(int i=0;i<a.length();i++){
        if(a[i]!=b[i]){
            x++;
        }

        if(x>4){
            return false;
        }
    }
    
    return x==4 || x==0;
}

void dfs(const string& c, const vector<string>& strs, unordered_set<string>& vis) {
    if(vis.find(c)!=vis.end()){
        return;
    }

    vis.insert(c);
    
    for(const string& str:strs) {
        if(sim(c,str)){
            dfs(str,strs,vis);
        }
    }
}

int getAnagramGroups(const vector<string>& strs) {
    int count=0;
    unordered_set<string>vis;
    
    for(const string& c:strs){
        if(vis.find(c)==vis.end()){
            dfs(c,strs,vis);
            count++;
        }
    }
    
    return count;
}

int main() {
    int n;
    cin >> n;
    vector<string> arr(n);
    
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    int groups = getAnagramGroups(arr);
    cout << groups << endl;
    
    return 0;
}
