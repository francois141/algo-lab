#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;


void solve() {
  
  int n;
  cin >> n;
  
  vector<int> a(n);
  
  for(int i = 0; i < n;i++) {
    cin >> a[i];
  }
  
  partial_sum(a.begin(), a.end(), a.begin(),plus<int>());
  
  int evens = count_if(a.begin(), a.end(),[](int x) -> int {
    return x % 2 == 0;
  });
  
  int odds = count_if(a.begin(), a.end(),[](int x) -> int {
    return x % 2 == 1;
  });
  
  cout << (evens*(evens-1) + odds*(odds-1)) / 2 + evens << "\n";
  
  return;
}


int main() {
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
  
  return 0;
}
