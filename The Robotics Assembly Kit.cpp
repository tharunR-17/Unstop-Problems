#include <iostream>
#include <unordered_map>
#include <string>
#include <climits>
using namespace std;

int user_logic(int n, int m, const string& belt,
               const unordered_map<char, int>& requirements) {

    unordered_map<char, int> window;

    int left = 0;
    int formed = 0;   // Number of required types currently satisfied
    int required = requirements.size();

    int ans = INT_MAX;

    for (int right = 0; right < n; ++right) {

        char c = belt[right];

        // Only track characters that are required
        if (requirements.count(c)) {
            window[c]++;

            // This type has just reached its required count
            if (window[c] == requirements.at(c)) {
                formed++;
            }
        }

        // Current window satisfies all requirements
        while (formed == required) {

            ans = min(ans, right - left + 1);

            char leftChar = belt[left];

            if (requirements.count(leftChar)) {
                window[leftChar]--;

                // It no longer satisfies its requirement
                if (window[leftChar] < requirements.at(leftChar)) {
                    formed--;
                }
            }

            left++;
        }
    }

    return (ans == INT_MAX) ? -1 : ans;
}

int main() {
    int n, m;
    cin >> n >> m;

    string belt;
    cin >> belt;

    unordered_map<char, int> requirements;

    for (int i = 0; i < m; ++i) {
        char component_type;
        int count;
        cin >> component_type >> count;

        requirements[component_type] = count;
    }

    int result = user_logic(n, m, belt, requirements);

    cout << result << endl;

    return 0;
}
