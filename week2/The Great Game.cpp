#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

vector<vector<int>> graph;
vector<vector<int>> dp;

int distance(int idx,int player) {
  
  if(dp[idx][player] != -1) {
    return dp[idx][player];
  }
  
  if(idx == graph.size() - 1)
    return 0;

  vector<int> v(0);
  for(auto next : graph[idx]) {
    v.push_back(distance(next,1-player));
  }
  
  int dist = player % 2 == 0 ?  *min_element(v.begin(),v.end()) : *max_element(v.begin(),v.end());
  dist++;
  
  dp[idx][player] = dist;
  
  return dist;
}

void solve()  {
  
  int n,m;
  cin >> n >> m;
  
  int r,bl;
  cin >> r >> bl;
  r--;
  bl--;
  
  graph = vector<vector<int>>(n,vector<int>(0));
  for(int i = 0; i < m;i++) {
    int a,b;
    cin >> a >> b;
    graph[a-1].push_back(b-1);
  }
  
  dp = vector<vector<int>>(n,vector<int>(2,-1));
  
  int dist_red   = distance(r,0);
  int dist_black = distance(bl,0);
  
  if(dist_red < dist_black) {
    cout << 0 << "\n";
  } else if(dist_black < dist_red){
    cout << 1 << "\n";
  } else {
    cout << (dist_red % 2 == 0) << "\n";
  }
  
  return;
}

int main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int t;
  cin >> t;
  
  while(t--) {
    solve();
  }
}
