#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int m, q;
    cin >> m;
    vector<int> permutation(m);
    for (int i = 0; i < m; i++) {
        permutation[i] = i + 1;
    }
    
    cin >> q;
    vector<int> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i];
    }
    
    vector<int> result(q);
    
    for (int i = 0; i < q; i++) {
        int query = queries[i];
        int index = find(permutation.begin(), permutation.end(), query) - permutation.begin();
        
        result[i] = index;
        
        // Move the query element to the beginning of the permutation
        rotate(permutation.begin(), permutation.begin() + index, permutation.begin() + index + 1);
    }
    
    // Print the result
    for (int i = 0; i < q; i++) {
        cout << result[i] << " ";
    }
    
    cout << endl;
    
    return 0;
}
