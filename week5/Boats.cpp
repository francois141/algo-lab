///1
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

    int best_score = INT_MAX;
    
    while(idx < n) {
      int position = boats[idx].position;
      int length = boats[idx].length;
      
      if(position >= best_score) break;

      best_score = min(best_score,max(last_position,position-length) + length);
      idx++;
    }
    
    max_score++;
    last_position = best_score;
  }
  
  cout << max_score << "\n";
}

signed main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
