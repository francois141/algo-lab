#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#define int long long

using namespace std;

int n,m,a,b,P,W,H;
vector<pair<int,int>> A; 
vector<int> B;
  
vector<vector<int>> compute() {

  vector<vector<int>> dp(n+1,vector<int>(H+1,0));
  vector<vector<int>> dp_next = dp;

  for(int i = 0; i < n;i++) {
    for(int k = 1; k <= n;k++) {
      for(int h = 0; h <= H;h++) {
        if(h - A[i].second > 0 && dp[k-1][h - A[i].second] == 0) {
          dp_next[k][h] = dp[k][h];
        }
        else {
          dp_next[k][h] = max(dp[k][h],dp[k-1][max(h - A[i].second,0LL)] + A[i].first);
        }
      }
    }
    dp = dp_next;
  } 

  
  return dp;
}

void solve() {
  
  cin >> n >> m >> a >> b >> P >> H >> W;
  
  A = vector<pair<int,int>>(n);
  B = vector<int>(m);
  
  for(int i = 0; i < n;i++) {
    int p,h;cin >> p >> h;
    A[i] = make_pair(p,h);
  }
  
  for(int i = 0; i < m;i++) {
    cin >> B[i];
  }
  
  sort(B.begin(),B.end(),greater<int>());
  
  int ans = LLONG_MAX;
  vector<vector<int>> dp = compute();
  
  for(int i = 0; i <= m;i++) {
    int W_tmp = 0,P_tmp = 0,H_tmp = 0;

    for(int idx = 0; idx < i;idx++) {
      W_tmp += B[idx];
    }
    
    int j = 0;
    while(j < n && (P_tmp < (P + i*b) || H_tmp < H)) {
      P_tmp = dp[j+1][H];
      H_tmp = H;
      j++;
    }
    
    if(P_tmp >= (P + i*b) && W_tmp >= (W + j*a) && H_tmp >= H) {
      ans = min(ans,i + j);
    }
  }
  
  ans = (ans == LLONG_MAX) ? -1 : ans;
  
  cout << ans << "\n"; 
  
  return;
}

signed main() {
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
  
  return 0;
}
