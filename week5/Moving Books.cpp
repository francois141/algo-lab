#include <iostream>
#include <vector>
#include <algorithm>

#define int long long

using namespace std;

void solve() {
  
  int n,m;
  cin >> n >> m;
  
  vector<int> s(n);
  vector<int> w(m);
  
  for(int i = 0; i < n;i++) {
    cin >> s[i]; 
  }
  
  for(int j = 0; j < m;j++) {
    cin >> w[j];
  }
  
  sort(s.begin(),s.end(),greater<int>());
  sort(w.begin(),w.end(),greater<int>());
  
  if(s[0]< w[0]) {
    cout << "impossible\n";
    return;
  }
  
  // Nb of boxes per personns
  vector<int> num_boxes(n,0);
  int max_box = 1;
  
  // First person takes the first box (greedy choice)
  num_boxes[0]++;
  
  // Then we iteratively add boxes
  for(int i = 1; i < m; i++) {
    
    // Check which persons can take this box
    int next_person = upper_bound(num_boxes.begin(),num_boxes.end(),max_box,greater<int>()) - num_boxes.begin();
    
    // Until is the index at which people become too weak to wear the boxes
    int until = upper_bound(s.begin(),s.end(),w[i],greater<int>()) - s.begin();
    
    // If the next person is too weak ==> increase capacity : else take it
    if(next_person < until) {
      num_boxes[next_person]++;
    } else {
      num_boxes[0]++;
      max_box++;
    }
  }
  
  // Print the result
  cout << (max_box - 1) * 3 + 2 << endl;
}

signed main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
  
  return 0;
}
