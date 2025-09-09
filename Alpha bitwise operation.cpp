#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int alpha_bitwise_operation(int n, std::vector<int>& arr)
{
    int result = 0;
    // Loop through each bit position (0 through 31)
    for (int bit = 0; bit < 32; ++bit)
    {
        int count = 0;
        // Count how many numbers have the current bit set
        for (int i = 0; i < n; i++)
        {
            if (arr[i] & (1 << bit))
                count++;
        }
        // Set the bit in result if count is greater than half of n
        if (count > n / 2)
            result |= (1 << bit);
    }
    return result;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> arr[i];
    }


    assert(arr.size() == n);

    int result = alpha_bitwise_operation(n, arr);
    std::cout << result << std::endl;

    return 0;
}
