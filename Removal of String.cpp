#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
using namespace std;

string removeDuplicatesAndReverse(const string& s)
{
    string result;
    unordered_set<char> seen;
    for (auto it = s.rbegin(); it != s.rend(); ++it) 
    {
        char c = *it;
        if (seen.count(c) == 0) 
        {
            result.push_back(c);
            seen.insert(c);
        }
    }
    return result;
}

string applyOperations(const string& s)
{
    string current = s;
    while (true) 
    {
        unordered_set<char> seen;
        bool hasDuplicates = false;
        for (char c : current) 
        {
            if (seen.count(c) > 0) 
            {
                hasDuplicates = true;
                break;
            }
            seen.insert(c);
        }
        if (hasDuplicates) 
        {
            current = removeDuplicatesAndReverse(current);
        }
        else 
        {
            break;
        }
    }
    return current;                             
}

int main()
{
   string s;
    cin >> s;
    string result = applyOperations(s);
    cout << result << endl;
    return 0;
}
