#include <bits/stdc++.h>

using namespace std;

#define int long

vector<vector<int>> graph;
vector<int> prices;

struct City {
  int noNeed;
  int need;
  int hasCity;
};

int min(City c) {
  return min(c.noNeed,min(c.need,c.hasCity));
}

City compute(int idx) {
  
  if(graph[idx].size() == 0) return City{prices[idx],0,prices[idx]};
  
  vector<City> childs = vector<City>(0);
  for(auto child : graph[idx]) childs.push_back(compute(child));
  
  int hasCity = prices[idx];
  for(City c : childs) hasCity += min(c);
  
  int noNeed = 0;
  int diff = LONG_MAX;
  for(City c : childs) {
    noNeed += c.noNeed;
    diff = min(c.hasCity - c.noNeed,diff);
  }
  if(diff > 0) noNeed += diff;
  
  int need = 0;
  for(City c : childs) need += min(c.hasCity,c.noNeed);
  
  return {min(noNeed,hasCity),need,hasCity};
}

void solve() {
  int n; cin >> n;
  
  graph = vector<vector<int>>(n,vector<int>(0));
  prices= vector<int>(n);
  
  for(int i = 0; i < n-1;i++) {
    int from,to;
    cin >> from >> to;
    graph[from].push_back(to);
  }
  
  for(int i = 0;i < n;i++) cin >> prices[i];
  
  City c = compute(0);
  
  cout << min(c.noNeed,c.hasCity) << endl;
}

signed main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0); 
  
  int t; cin >> t;
  
  while(t--)
    solve();
}
