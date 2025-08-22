#include <bits/stdc++.h>
using namespace std;

std::string checkSymbolicStability(std::string& S) 
{
    if(S.length()%2)
    {
        return "UNSTABLE";
    }
    for(int i=1;i<S.length();i++)
    {
        if(S[i]==S[i-1])
        {
            return "UNSTABLE";
        }
    }
    sort(S.begin(),S.end());
    int a=1;
    for(int i=1;i<S.length();i++)
    {
        if(S[i]==S[i-1])
        {
            a++;
        }
        else
        {
            if(a%2)
            {
                return "UNSTABLE";
            }
            a=1;
        }
    }
    return "STABLE";
}

int main() {
    std::string S;
    std::getline(std::cin, S); // Read the entire line as input

    // Call the user logic function and print the result
    std::string result = checkSymbolicStability(S);
    std::cout << result << std::endl;

    return 0;
}
