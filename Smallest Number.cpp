#include <bits/stdc++.h>
using namespace std;

int solve(vector<int> arr)
{
  int res = 1; // initializing res as 1 
  for (int i = 0; i < arr.size() && arr[i] <= res; i++) // iterating over the array until res is greater than or equal to current element
  {
      res = res + arr[i]; // incrementing the res
  }
  return res;  // returning the ans
}

int main() 
{
  int n;
  cin>>n;
  
  vector<int>arr(n);
  for(int i=0;i<n;i++)
  {
    cin>>arr[i];
  }
  cout<<solve(arr);
  return 0;
}
