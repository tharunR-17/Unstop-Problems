#include <iostream>
#include <vector>
#include <map> 
using namespace std;


int minUnassignedShifts(int n, int m, const vector<int>& doctorSpecs, const vector<int>& shiftReqs) {
    
    map<int, int> doctorCounts;

    for (int spec : doctorSpecs) {
        doctorCounts[spec]++;
    }

    int unassignedShifts = 0;

    for (int req : shiftReqs) {
        if (doctorCounts[req] > 0) {
            doctorCounts[req]--; 
        } else {
            unassignedShifts++;
        }
    }

    return unassignedShifts;
}

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0; 
    
    vector<int> doctorSpecs(n);
    vector<int> shiftReqs(m);

    for (int i = 0; i < n; ++i) {
        cin >> doctorSpecs[i]; 
    }

    for (int i = 0; i < m; ++i) {
        cin >> shiftReqs[i]; 
    }

    // Call the user logic function and print the result
    int result = minUnassignedShifts(n, m, doctorSpecs, shiftReqs);
    cout << result << endl;

    return 0;
}
