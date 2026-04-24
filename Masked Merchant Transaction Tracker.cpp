#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

int count_suspicious_transactions(const std::vector<std::string>& suspicious_ids, const std::vector<std::string>& transaction_patterns) {
    // Write your logic here to determine the number of suspicious transactions.
    std::unordered_set<std::string> id_set(suspicious_ids.begin(), suspicious_ids.end());
    int count = 0;
    for (const std::string& pattern : transaction_patterns) {
        bool found = false;
        for (const std::string& id : suspicious_ids) {
            if (id.length() != pattern.length()) {
                continue;
            }
            bool match = true;
            for (int i = 0; i < (int)pattern.length(); i++) {
                if (pattern[i] != '*' && pattern[i] != id[i]) {
                    match = false; 
                    break; 
                }
            }
            if (match) { 
                found = true; break; 
            }
        }
        if (found) {
            count++;
        }
    }
    return count;
}

int main() {
    int N, M;
    std::cin >> N;
    std::vector<std::string> suspicious_ids(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> suspicious_ids[i];
    }

    std::cin >> M;
    std::vector<std::string> transaction_patterns(M);
    for (int i = 0; i < M; ++i) {
        std::cin >> transaction_patterns[i];
    }

    int result = count_suspicious_transactions(suspicious_ids, transaction_patterns);
    std::cout << result << std::endl;

    return 0;
}
