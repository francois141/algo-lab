#include <bits/stdc++.h>

#define int long

using namespace std;

struct City {
  int repared;
  int noneed;
  int need;
};

vector<vector<int>> graph;
vector<int> costs;
vector<City> dp;

void compute(int idx) {
  // Base case
  if(graph[idx].size() == 0) {
    dp[idx] = {costs[idx],costs[idx],0};
    return;
  }
  
  // Recursive case
  City tmp = {0,0,0};
  for(auto child: graph[idx]) {
    compute(child);
  }
  
  // Case 1 
  tmp.repared = costs[idx];
  for(auto child: graph[idx]) {
    tmp.repared += min({dp[child].repared,dp[child].noneed,dp[child].need});

  }
  // Case 2
  int min_diff = INT_MAX;
  for(auto child: graph[idx]) {
    tmp.noneed += min({dp[child].repared,dp[child].noneed});
    min_diff = min(min_diff, dp[child].repared - dp[child].noneed);
  }
  tmp.noneed += max(0l,min_diff);
  tmp.noneed = min(tmp.repared,tmp.noneed);
  
  // Case 3
  for(auto child: graph[idx]) {
    tmp.need += min({dp[child].repared,dp[child].noneed});
  }

  dp[idx] = tmp;
}

void solve() {
  int n;
  cin >> n;
  
  graph = vector<vector<int>>(n,vector<int>(0));
  for(int i = 0; i < n-1;i++) {
    int from; 
    int to;
    cin >> from >> to;
    graph[from].push_back(to);
  }
  
  costs =  vector<int>(n);
  for(int i = 0; i < n;i++) cin >> costs[i];
  
  dp = vector<City>(n);
  
  compute(0);
  cout << min(dp[0].repared, dp[0].noneed) << "\n";
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
