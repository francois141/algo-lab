#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> graph;

vector<int> t;
set<int> s;
multiset<int> values;
deque<int> path;
vector<int> p;

int n,m,k;

void dfs(int idx) {
  
  if(path.size() == m) { 
    
    int minT = *values.begin();
    int maxT = *values.rbegin();
  
    if(maxT - minT <= k) {
      s.insert(path[0]);
    }
  } 

  for(int next : graph[idx]) {

    path.push_back(next);
    values.insert(t[next]);
     
    if(path.size() > m) {
      values.erase(values.find(t[path[0]]));
      path.pop_front();
    }
    
    dfs(next);
    
    if(path[0] != 0) {
      int p_idx = p[path[0]];
      path.push_front(p_idx);
      values.insert(t[p_idx]);
    }
    
    values.erase(values.find(t[next]));
    path.pop_back();
  }
}

void solve() {

  cin >> n >> m >> k;
  
  t = vector<int>(n);
  for(int i = 0; i < n;i++) cin >> t[i];
  
  p = vector<int>(n,0);
  graph = vector<vector<int>>(n,vector<int>(0));
  for(int i = 0; i < n-1;i++) {
    int from,to; cin >> from >> to;
    graph[from].push_back(to);
    p[to] = from;
  }
  
  s = set<int>();
  values = multiset<int>();
  
  path = deque<int>(0);
  path.push_back(0);
  values.insert(t[0]);
  
  dfs(0);

  if(s.empty()) {
    cout << "Abort mission"; 
  }
  else {
    for(int tmp : s) {
      cout << tmp << " ";
    }
  }
  cout << "\n";
  
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
