#include <bits/stdc++.h>
#include <string>
using namespace std;
#define ll long long int
bool isPrime(ll n)
{
  if (n <= 1)
    return false;
  for (ll i = 2; i * i <= n; i++) {
    if (n % i == 0)
      return false;
  }
  return true;
}
ll solve(string str)
{
  ll ans=0;
  unordered_map<char, ll>mp; // initializing unordered_map of char and long long int
  for(auto i : str) // iterating over the string
  {
    mp[i]=max((ll)1, (ll)mp[i]); // updating mp[i] to 1 if it's 0
    
    char first = i-2; // checking for predecessor
    char second = i+2; // checking for successor
    
    mp[i] = max({(ll)1, mp[i], mp[first]+1, mp[second]+1}); // updating the mp[i] by checking predecessor and successor
    ans=max(ans, mp[i]); // updating the ans
  }
  return ans; // returning the ans
} 

int main()
{
  string s;
  cin>>s;
  
  cout<<isPrime(solve(s));
  return 0;
}
