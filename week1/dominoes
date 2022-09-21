#include <iostream>
#include <vector>

using namespace std;

void solve() {
  
  int n;
  cin >> n;
  
  vector<int> a(n);
  for(int i = 0; i < n;i++) {
    cin >> a[i];
  }
  
  int position = 0;
  int until = 1;
  
  while(position < n && position < until) {
    until = max(until,position + a[position]);
    position++;  
  } 
  
  cout << min(position,n) << "\n";
  
  return;
}


int main() {
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
  
  return 0;
}
