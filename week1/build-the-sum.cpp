#include <iostream>
#include <vector>
#include <numeric>

void solve() {
  
  int n; 
  std::cin >> n;
  
  std::vector<int> a(n);
  
  for(int i = 0; i < n;i++) {
    std::cin >> a[i];
  }
  
  std::cout << std::accumulate(a.begin(),a.end(),0) << "\n";
}

int main() {
  
  int t; 
  std::cin >> t;
  
  while(t--)
    solve();
  
  return 0;
}
