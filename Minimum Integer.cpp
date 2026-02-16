#include <iostream>
#include <vector>

int user_logic(int n, std::vector<int> &arr);

int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    int result = user_logic(n, arr);
    std::cout << result << std::endl;
    return 0;
}

int user_logic(int n, std::vector<int> &arr) {
    // Write your logic here
    int res=arr[0];
    for(int i=1;i<n;i++) {
        res&=arr[i];
    }
    return res;
}
