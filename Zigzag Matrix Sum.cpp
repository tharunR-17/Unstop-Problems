#include <iostream>
#include <vector>
using namespace std;

// Function to calculate the sum of elements in zigzag pattern
int zigzagSum(const vector<vector<int>>& matrix) 
{
    int a=0;
    for(int i=0;i<matrix.size();i++)
    {
        for(int j=0;j<matrix[i].size();j++)
        {
            a+=matrix[i][j];
        }
    }
    return a; // Placeholder return statement
}

int main() {
    int n, m;
    cin >> n >> m;

    // Initialize the matrix
    vector<vector<int>> matrix(n, vector<int>(m));

    // Input matrix elements
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }

    // Call the function to calculate the sum
    int result = zigzagSum(matrix);

    // Output the result
    cout << result << endl;

    return 0;
}
