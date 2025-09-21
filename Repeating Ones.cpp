#include <iostream>
#include <string>

int RepeatingOnes(const std::string& bst) {
    // Write your logic here.
    int left=0,count=0,ans=0;
    while(left<bst.size()){
        if(bst[left]=='1')
        count++;
        else{
            ans+=(count*(count+1))/2;
            count=0;
        }
        left++;
    }
    if(count!=0)
         ans+=(count*(count+1))/2;
    return ans;
}

int main() {
    std::string binary_string;
    std::getline(std::cin, binary_string);
    
    int result = RepeatingOnes(binary_string);
    std::cout << result << std::endl;
    return 0;
}
