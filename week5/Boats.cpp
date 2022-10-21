#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

typedef struct boat {
  int length;
  int pos;
} boat;

void solve() {
  
  int n;
  cin >> n;
  
  vector<boat> boats(0);
  for(int i = 0; i < n;i++) {
    int l,p;
    cin >> l >> p;
    boats.push_back({l,p});
  }
  
  sort(boats.begin(),boats.end(),[&](const boat &a,const boat &b) -> bool {
    return a.pos < b.pos;
  });
  
  int pos_last = INT_MIN;
  int score = 0;
  int last_index = -1;
  
  while(true) {
    
    int current_score = INT_MAX;
    bool found = false;
    
    int i = last_index + 1;
    
    while(i < n) {
      
      int position = boats[i].pos;
      int length = boats[i].length;
      
      int boat_start = max(pos_last, position - length);
      
      if(boat_start > position) {
        i++;
        continue;
      }
      
      if(boat_start > current_score) {
        break;
      }

      int end = boat_start + length;
      if(end < current_score) {
        current_score = end;
        found = true;
        last_index = i;
      }
      i++;
    }
    
    if(!found) {
      break;
    } 
    else {
      pos_last = current_score;
      score++;
    }
    
  }
  
  cout << score << "\n";
  
  return;
}

int main() {
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
  
  return 0;
}
