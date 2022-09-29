#include <iostream>
#include <vector>

using namespace std;

vector<int> a;
vector<vector<int>> dp;

int compute(int start, int end, int player) {
  
  if(dp[start][end] != -1)
    return dp[start][end];
  
  if(start >= end) {
    return player == 0 ? a[start] : 0;
  }
  
  if(player == 1) {
    dp[start][end] = min(compute(start+1,end,0),compute(start,end-1,0));
  }
  
  else {
    dp[start][end] = max(a[start]+compute(start+1,end,1),a[end]+compute(start,end-1,1));
  }
  
  return dp[start][end];
}

void solve() {
  
  int n;
  cin >> n;
  
  a = vector<int>(n);
  dp = vector<vector<int>>(n,vector<int>(n,-1));
  for(int i = 0; i < n;i++) {
    cin >> a[i];
  }
  
  if(n == 1) {
    cout << a.back() << "\n";
    return;
  }

  int output = max(a[0]+compute(1,n-1,1),a.back()+compute(0,n-2,1));
  
  cout << output <<"\n";
}

int main() {
  
  int t; 
  cin >> t;
  
  while(t--)
    solve();
  
}
