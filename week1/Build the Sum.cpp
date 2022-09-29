#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

void solve() {
  
  int n; 
  cin >> n;
  
  vector<int> a(n);
  
  for(int i = 0; i < n;i++) {
    cin >> a[i];
  }
  
  cout << accumulate(a.begin(),a.end(),0) << "\n";
}

int main() {
  
  int t; 
  cin >> t;
  
  while(t--)
    solve();
  
  return 0;
}
