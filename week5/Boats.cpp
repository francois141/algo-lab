#include <bits/stdc++.h>

using namespace std;

struct Boat {
  int position;
  int length;
};

void solve() {
  
  int n;
  cin >> n;
  
  vector<Boat> boats(n);
  for(int i = 0; i < n;i++) {
    cin >> boats[i].length;
    cin >> boats[i].position;
  }
  
  sort(boats.begin(),boats.end(), [](auto b1,auto b2) {
    return b1.position < b2.position;
  });
  
  int max_score = 0;
  
  int last_pos = INT_MIN;
  int idx = 0;
  
  while(idx != n) {
    
    int cur_pos = INT_MAX;
    
    while(idx != n) {
      if(boats[idx].position >= cur_pos) {
        max_score++;
        last_pos = cur_pos;
        break;
      }
      if(cur_pos > max(boats[idx].position-boats[idx].length,last_pos) + boats[idx].length) {
        cur_pos = max(boats[idx].position-boats[idx].length,last_pos) + boats[idx].length;
      }
      
      idx++;
    }
    
  }
  

  cout << max_score+1 << "\n";
}

signed main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
