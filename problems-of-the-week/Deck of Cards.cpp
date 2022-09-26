#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <numeric>
using namespace std;


void solve() {
  
  int n,k;
  cin >> n >> k;
  
  vector<int> a(0);

  for(int i = 0; i < n;i++) {
    int tmp;
    cin >> tmp;
    a.push_back(tmp);
  }

  int left = -1;
  int right = 0;
  
  int best = INT_MAX;
  int l1 = -1,l2 = -1;
  
  int sum = 0;
  
  while(left != n-1) {
    
    left++;
    sum += a[left];
    
    if(abs(sum - k) < best) {
      best = abs(sum - k);
      l1 = right;
      l2 = left;
    }

    while(left != right && sum - k > 0) {

      sum -= a[right];
      right++;
      
      if(abs(sum - k) < best) {
        best = abs(sum - k);
        l1 = right;
        l2 = left;
      }
    }
    
  }
  
  cout << l1 << " " << l2 << "\n";
}

int main() {
  
  int t;
  cin >> t;
  
  while(t--) 
    solve();
  
  return 0;
}
