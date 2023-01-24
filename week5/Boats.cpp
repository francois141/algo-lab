#include <bits/stdc++.h>

#define int long

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
  int last_position = INT_MIN;
  int idx = 0;
  
  while(idx < n) {
    int current_position = INT_MAX;
    
    while(idx < n) {
      int position = boats[idx].position;
      int length = boats[idx].length;
      int start = position - length;
      
      if(position >= current_position) {
        max_score++;
        last_position = current_position;
        break;
      }
      
      current_position = min(current_position,max(start,last_position) + length);
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
