#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int calculate_minimum_waste(int N, int M, vector<int> item_lengths, vector<int> roll_lengths) 
{
    sort(item_lengths.begin(), item_lengths.end());
    sort(roll_lengths.begin(), roll_lengths.end());

    int i = 0, j = 0;
    int total_waste = 0;

    while (i < N && j < M)
    {
        if (roll_lengths[j] >= item_lengths[i])
        {
            total_waste += (roll_lengths[j] - item_lengths[i]);
            i++;
            j++;
        }

        else
        {
            j++;
        }
    }

    if (i < N)
        return -1;

    return total_waste;
}

int main() 
{
    int N, M;
    cin >> N >> M;

    vector<int> item_lengths(N), roll_lengths(M);

    for (int i = 0; i < N; ++i)
    {
        cin >> item_lengths[i];
    }

    for (int i = 0; i < M; ++i) 
    {
        cin >> roll_lengths[i];
    }

    int result = calculate_minimum_waste(N, M, item_lengths, roll_lengths);
    cout << result << endl;

    return 0;
}
