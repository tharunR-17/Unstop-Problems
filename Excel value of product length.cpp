#include <bits/stdc++.h>
using namespace std;

int maxProduct(vector<string>& words) {
	int n = words.size(), ans = 0;
	vector<int> mask(n);
	for(int i = 0; i < n; i++) {
		for(auto& ch : words[i])           
			mask[i] |= 1 << (ch - 'a');     // hash the word
		for(int j = 0; j < i; j++)
			if((mask[i] & mask[j]) == 0)    // no common set bit in the hash of words[i] and words[j]
				ans = max(ans, int(words[i].size() * words[j].size()));
	}   
	return ans;
}

void printString(int n)
{
    char str[100000]; // To store result (Excel column name)
    int i = 0; // To store current index in str which is result
 
    while (n > 0) {
        // Find remainder
        int rem = n % 26;
 
        // If remainder is 0, then a 'Z' must be there in output
        if (rem == 0) {
            str[i++] = 'Z';
            n = (n / 26) - 1;
        }
        else // If remainder is non-zero
        {
            str[i++] = (rem - 1) + 'A';
            n = n / 26;
        }
    }
    str[i] = '\0';
 
    // Reverse the string and print result
    reverse(str, str + strlen(str));
    cout << str << endl;

}

int main() {
	// your code goes here
	int n;
	cin>>n;
	vector<string> words(n);
	for(int i=0;i<n;++i)
	{
		cin>>words[i];
	}
	int x=maxProduct(words);
	printString(x);
	return 0;
}
