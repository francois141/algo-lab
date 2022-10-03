#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#define int long long

using namespace std;

void solve() {
  
  int n,m,x,k;
  cin >> n >> m >> x >> k;
  
  vector<vector<pair<int,int>>> graph = vector<vector<pair<int,int>>>(n,vector<pair<int,int>>(0));
  vector<bool> hasOutgoing = vector<bool>(n,false);
  
  for(int i = 0; i < m;i++) {
    int from,to,reward;
    cin >> from >> to >> reward;
    graph[to].push_back(make_pair(from,reward));
    hasOutgoing[from] = true;
  }
  
  vector<vector<int>> dp = vector<vector<int>>(k+1,vector<int>(n,LLONG_MIN));
  dp[0][0] = 0;
  
  for(int step = 1; step <= k;step++) {
    
    for(int i = 1; i < n;i++) {
      for(auto transition : graph[i]) {
        int from = transition.first;
        int reward = transition.second;
        dp[step][i] = max(dp[step][i],dp[step-1][from] + reward);
      }
      
      if(dp[step][i] >= x) {
        cout << step << "\n";
        return;
      }
    }
    
    for(int i = 1; i < n;i++) {
      if(!hasOutgoing[i]) {
        dp[step][0] = max(dp[step][0],dp[step][i]); 
      }
    }
  }
  
  cout << "Impossible" << "\n";
  
  return;
}

signed main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);  
  
  int t;
  cin >> t;
  
  while(t--) 
    solve();
  
  return 0;
}
