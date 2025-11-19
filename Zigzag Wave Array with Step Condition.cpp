#include <iostream>
#include <vector>
#include <algorithm> 
void wave_sort(std::vector<int>& arr, int n) {

    for (int i = 0; i < n - 1; i += 2) {

        std::swap(arr[i], arr[i+1]);
    }
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T, N;
    if (std::cin >> T) {
        while (T--) {
            std::cin >> N;
            std::vector<int> arr(N);
            for (int i = 0; i < N; ++i) {
                std::cin >> arr[i];
            }
            
            wave_sort(arr, N);
            
            for (int i = 0; i < N; ++i) {
                std::cout << arr[i] << " ";
            }
            std::cout << "\n";
        }
    }
    return 0;
}
