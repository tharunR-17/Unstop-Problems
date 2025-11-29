#include <bits/stdc++.h>
using namespace std;

// Define a structure for the request
struct Request {
    string type;
    int row;
    Request(string t, int r) : type(t), row(r) {}
};

// Placeholder function for user logic

vector<string> allocateSeats(int N, vector<Request> &requests) {
    vector<map<string, int>> bus(N + 1); 
    for (int i = 1; i <= N; ++i) {
        bus[i]["W"] = 2;
        bus[i]["A"] = 2;
    }

    vector<string> result;

    for (auto &req : requests) {
        string seat_type = req.type;
        int row_pref = req.row;

        bool allocated = false;

        if (row_pref != -1) {
            if (bus[row_pref][seat_type] > 0) {
                bus[row_pref][seat_type]--;
                result.push_back("Row " + to_string(row_pref) + " Seat " + seat_type);
                allocated = true;
            }
        } else {
            for (int i = 1; i <= N; ++i) {
                if (bus[i][seat_type] > 0) {
                    bus[i][seat_type]--;
                    result.push_back("Row " + to_string(i) + " Seat " + seat_type);
                    allocated = true;
                    break;
                }
            }
        }

        if (!allocated) {
            result.push_back("Rejected");
        }
    }

    return result;
}

int main() {
    int N, M;
    cin >> N >> M;  // Read number of rows and number of requests
    
    vector<Request> requests;
    for (int i = 0; i < M; ++i) {
        string S;
        int R;
        cin >> S >> R;  // Read each request
        requests.emplace_back(S, R);
    }
    
    // Call the user logic function
    vector<string> results = allocateSeats(N, requests);
    
    // Output the results
    for (const string &result : results) {
        cout << result << endl;
    }
    
    return 0;
}
