#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct entry {
  int word;
  int position;
};
  
void solve() {
  
  int n;
  cin >> n;
  
  vector<int> m(n);
  for(int i = 0; i < n;i++) 
    cin >> m[i];
  
  vector<entry> words(0);
  
  for(int i = 0; i < n;i++) {
    for(int j = 0; j < m[i];j++) {
      int tmp;
      cin >> tmp;
      words.push_back({i,tmp});
    }
  }
  
  sort(words.begin(),words.end(), [](entry a,entry b) -> bool {
    return a.position < b.position;
  });
  
  int start = -1;
  int end = 0;
  
  int best = INT_MAX;
  
  vector<int> pos(n,-1);
  int count = 0;
  
  while(start != words.size() - 1 ) {
    start++;
    
    int word = words[start].word;
    int position = words[start].position;
    
    if(pos[word] == -1) 
      count++;
      
    pos[word] = position;
    
    while(pos[words[end].word] != words[end].position) {
      end++;
    }
    
    if(count == n) {
      best = min(best,words[start].position - words[end].position + 1);
    }
    
  }
  
  cout << best << "\n";
  
  return;
}

int main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int t;
  cin >> t;
  
  while(t--) 
    solve();
  
}
