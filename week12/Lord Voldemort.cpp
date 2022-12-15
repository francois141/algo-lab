#include <bits/stdc++.h>

#define int long 

using namespace std;

void solve() {
  
  int n,m,k;
  cin >> n >> m >> k;
  
  vector<vector<int>> dp(m+1,vector<int>(n+1,0));
  vector<int> h(n+1,0);
  
  for(int i = 1; i <= n;i++) {
    cin >> h[i];
  }
  
  partial_sum(h.begin(),h.end(),h.begin());
  
  for(int i = 1; i <= n;i++) {
    
    // Part 1 : Find a good index
    int target = h[i] - k;
    auto it = std::lower_bound(h.begin(), h.end(), target);
    int j = it - h.begin(); 
    bool possible = *it == target ? true : false; 
    
    // Part 2 : Update dp table
    int toAdd = i-j;
      
    // First person
    if(possible) {
      dp[1][i] = toAdd;
    }
    dp[1][i] = max(dp[1][i],dp[1][i-1]);
  
    for(int p = 2; p <= m;p++) {
  
      // Initialize with previous state
      dp[p][i] = dp[p][i-1];

      // Check if we can update the data
      if(possible && dp[p-1][j] != 0){
        dp[p][i] = max(dp[p][i],dp[p-1][j] + toAdd);
      } 
    }   
  }
  
  if(dp.back().back() == 0)
    cout << "fail" << "\n";
  else
    cout << dp.back().back() << "\n";
    
  return;
}
  

signed main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t; cin >> t;
  
  while(t--)
    solve();
  
  return 0;
}
