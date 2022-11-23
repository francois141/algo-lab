#include <bits/stdc++.h>

using namespace std;

void solve() {
  
  int n;
  cin >> n;
  
  vector<int> a(n+1,0);
  vector<int> b(n+1,0);
  
  for(int i = 1; i <= n;i++) {
    cin >> a[i]; 
    a[i] += a[i-1];
  }
  for(int j = 1; j <= n;j++) {
    cin >> b[j];
    b[j] += b[j-1];
  }

  vector<vector<int>> dp(n+1,vector<int>(n+1,INT_MAX));
  dp[0][0] = 0;
  
  for(int i = 1; i <= n;i++) {
    for(int j = 1; j <= n;j++) {
      for(int k = i-1; k >= 0;k--) {
        for(int l = j-1; l >= 0;l--) {
          if(dp[k][l] != INT_MAX) {
            dp[i][j] = min(dp[i][j],dp[k][l] + (a[i]-a[k]-(i-k)) * (b[j]-b[l]-(j-l)));
          }
          if((a[i]-a[k]-(i-k)) * (b[j]-b[l]-(j-l)) >= dp[i][j]) {
            break;
          }
        }
      }
    }
  }
    
  cout << dp.back().back() << "\n";
}

int main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
