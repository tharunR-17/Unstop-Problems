#include <iostream>
#include <vector>
#include <unordered_set>

void compute_notable_readings(int n, int k, std::vector<int> &v, std::vector<int> &s, std::vector<int> &result) {
    // Placeholder for user logic
    for(int i=0; i<n-k+1; i++){
        int max=0, dis=0;
        std::unordered_set<int> st;
        for(int j=i; j<i+k; ++j){
            max = v[j] > max? v[j]:max;
            st.insert(s[j]);
        }
        if(st.size()*2 >=k)
            result[i]=max;
        else
            result[i]=-1;
    }

}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> v(n);
    std::vector<int> s(n);
    std::vector<int> result(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> s[i];
    }
    compute_notable_readings(n, k, v, s, result);
    for (int i = 0; i < n-k+1; ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
