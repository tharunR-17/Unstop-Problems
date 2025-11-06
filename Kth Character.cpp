#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;
using ll = long long;

#define all(a)             (a).begin(), (a).end()
#define rall(a)            (a).rbegin(), (a).rend()
#define sz(a)              (int) ((a).size())
#define pb                 push_back
#define fi                 first
#define se                 second
#define f0r(i, a, b)       for(int i = (a); i < (b); ++i)
#define f0rr(i, a, b)      for(int i = (a - 1); i >= (b); --i)
#define trav(i, v)         for(auto &i : (v))

template<class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
template<typename T> T pow(T a, T b) { T res = 1; f0r(i, 0, b) res = res * a; return res; }
template<typename T> void ckmax(T &a, T b) { a = max(a, b);  }
template<typename T> void ckmin(T &a, T b) { a = min(a, b);  }

int dx4[] = {0, 1, 0, -1};
int dy4[] = {1, 0, -1, 0};
int dx8[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dy8[] = {-1, 0, 1, 1, 1, 0, -1, -1};

const int N2 = 1004, N = 200004;
const ll linf = 1000000000000000000;
const int inf = 1000010000;

int n, m, x, y;
vector<int> v(N), dp(N);
vector<vector<int>> mat(N2, vector<int> (N2));
// <===================================================================================================>

int main(){
   cin.tie(nullptr)->sync_with_stdio(false);

   clock_t time_req;  
   time_req = clock();
   
   int tt = 1;
   // cin >> tt;
   f0r(T, 1, tt + 1) {
      cin >> n >> m;
      string s;
      cin >> s;
      --m;
      while(sz(s) && m) {
         s.pop_back();
         --m;
      }
      cout << s.back() ;
   }
   
   time_req = clock() - time_req;
//    cerr << "Time Taken: "<< (float)time_req/CLOCKS_PER_SEC << " seconds" << "\n";
   
   return 0;
}
