#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void processLicenseData(int N, int C, vector<tuple<int, int, int, int>>& people, vector<int>& newLicenses, vector<int>& renewals) {
    // User should implement the logic here
    for (const auto& person : people) {
        int id  = std::get<0>(person);
        int age = std::get<1>(person);
        int yearOfExperience  = std::get<2>(person);
        int yearOfIssue = std::get<3>(person);
        
        if(age >= 18 && yearOfExperience >= 1 && yearOfIssue == 0){
            newLicenses.push_back(id);
        }
        if(C-yearOfIssue > 5 && yearOfIssue != 0){
            renewals.push_back(id);
        }
    }
}

int main() {
    int N, C;
    cin >> N >> C;

    vector<tuple<int, int, int, int>> people(N);
    for (int i = 0; i < N; ++i) {
        int id, age, experience, issueYear;
        cin >> id >> age >> experience >> issueYear;
        people[i] = make_tuple(id, age, experience, issueYear);
    }

    vector<int> newLicenses;
    vector<int> renewals;

    processLicenseData(N, C, people, newLicenses, renewals);

    if (newLicenses.empty()) {
        cout << "-1" << endl;
    } else {
        sort(newLicenses.begin(), newLicenses.end());
        for (int id : newLicenses) {
            cout << id << " ";
        }
        cout << endl;
    }

    if (renewals.empty()) {
        cout << "-1" << endl;
    } else {
        sort(renewals.begin(), renewals.end());
        for (int id : renewals) {
            cout << id << " ";
        }
        cout << endl;
    }

    return 0;
}
