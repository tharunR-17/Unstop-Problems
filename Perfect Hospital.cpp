#include <iostream>
#include <cmath>
#include <utility>

std::pair<int, int> find_nearest_hospital_code_and_distance(int N) {
    // Compute the largest perfect square less than or equal to N
    int sqrt_floor = static_cast<int>(std::sqrt(N));
    int nearest_hospital = sqrt_floor * sqrt_floor;
    int distance = N - nearest_hospital;

    return {nearest_hospital, distance};
}

int main() {
    int N;
    std::cin >> N;

    auto result = find_nearest_hospital_code_and_distance(N);

    std::cout << result.first << " " << result.second << std::endl;

    return 0;
}
