#include <bits/stdc++.h>

#define int long

using namespace std;

void solve() {
  int n;
  cin >> n;
  
  vector<int> a(n,0);
  vector<int> b(n,0);
  
  for(int i = 0; i < n;i++) cin >> a[i];
  for(int i = 0; i < n;i++) cin >> b[i];

  vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MAX));
  dp[0][0] = 0;
  
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int pred = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
      dp[i][j] = pred + (a[i - 1] - 1) * (b[j - 1] - 1);
    }
  }

  cout << dp.back().back() << "\n"; 
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
