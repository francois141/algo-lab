#include <bits/stdc++.h>

using namespace std;

void solve() {
  
  int n;
  cin >> n;
  
  vector<int> t(n);
  for(int i = 0; i < n;i++)
    cin >> t[i];
  
  for(int i = 1; i < n;i++) {
    int parent = (i - 1) / 2;
    t[i] = min(t[i],t[parent]-1);
  }
  
  sort(t.begin(),t.end());
  
  for(int i = 0; i < n;i++)  {
    if(t[i] <= i) {
      cout << "no" << "\n";
      return;
    }
  }
  
  cout << "yes" << "\n";
  return;
}

signed main() {

  int t;
  cin >> t;
  
  while(t--)
    solve();
  
  return 0;
}
