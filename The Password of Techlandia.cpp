#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
using namespace std;
void validate_password_and_find_most_frequent(int N, const std::vector<int>& password, std::string& validation_result, int& most_frequent_element) {
    unordered_map<int,int>umm;
    for(const auto &it:password){
        umm[it]++;
    }
    bool is_even=true;
    bool twice=false;
    for(const auto &pair:umm){
        if(pair.second % 2 ==1){
            is_even=false;
            break;
        }
        if(pair.second==2){
            twice=true;
        }
    }
    if(!is_even || !twice)validation_result="INVALID";
    else validation_result="VALID";
    int max_freq=0;
    most_frequent_element=INT_MAX;
    for(const auto &pair:umm){
        if(pair.second>max_freq||(pair.second==max_freq && pair.first<most_frequent_element)){
            max_freq=pair.second;
            most_frequent_element=pair.first;
        }
    }
}

int main() {
    int N;
    std::cin >> N;
    std::vector<int> password(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> password[i];
    }
    std::string validation_result;
    int most_frequent_element;
    validate_password_and_find_most_frequent(N, password, validation_result, most_frequent_element);
    std::cout << validation_result << std::endl;
    std::cout << most_frequent_element << std::endl;
    return 0;
}
