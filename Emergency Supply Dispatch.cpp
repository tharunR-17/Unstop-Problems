#include <iostream>
#include <vector>
#include <queue>

// Optimizes standard I/O operations for performance
void optimize_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    optimize_io();

    int total_elements = 0;
    int target_count = 0;
    
    if (!(std::cin >> total_elements >> target_count)) {
        return 0;
    }

    std::vector<int> stream_buffer(total_elements);
    for (int i = 0; i < total_elements; ++i) {
        std::cin >> stream_buffer[i];
    }

    // Initialize max-heap directly from the vector bounds
    std::priority_queue<int> max_heap(stream_buffer.begin(), stream_buffer.end());

    // Extract and print the top K largest elements
    for (int i = 0; i < target_count; ++i) {
        if (max_heap.empty()) break; 

        std::cout << max_heap.top();
        max_heap.pop();

        if (i < target_count - 1) {
            std::cout << ' ';
        }
    }
    std::cout << '\n';

    return 0;
}
