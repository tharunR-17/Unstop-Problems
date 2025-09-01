#include <iostream>
#include <vector>
#include <string>

int user_logic(int n, std::vector<std::string> &words) {
    // Write your logic here.
    if(n==1) return 1;
    for(int i=0; i<n-1; i++){
        std::string wordI = words[i];
        for(int j=i+1; j<= i+1; j++){
            std::string wordJ = words[j];
            if(wordI[wordI.size()-1] == wordJ[0]){
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> words(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> words[i];
    }
    int result = user_logic(n, words);
    std::cout << result << std::endl;
    return 0;
}
