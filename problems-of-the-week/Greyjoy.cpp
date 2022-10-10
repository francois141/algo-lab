#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long

typedef struct  {
  int value;
  int position;
  int way;
} island;

void solve() {
  
  int n,k,w;
  cin >> n >> k >> w;
  
  vector<int> c(n);
  for(int i = 0; i < n;i++) {
    cin >> c[i];
  }
  
  vector<vector<int>> ways(w,vector<int>(0));
  vector<island> islands(0);
  
  for(int i = 0; i < w;i++) {
    int l;
    cin >> l;
    vector<int> tmp(l,0);
    int sum = 0;
    for(int j = 0; j < l;j++) {
      cin >> tmp[j];
      if(j != 0) {
        sum += c[tmp[j]];
        islands.push_back({sum,j,i});
      }
    }
    ways[i] = tmp;
  }
  
  int best = 0;
  
  for(int i = 0; i < w;i++) {

    int start = -1;
    int end = 0;
    int score = 0;
    
    int length = ways[i].size();
    
    while(start < length - 1) {
    
      start++;
      score += c[ways[i][start]];

      while(score > k) {
        score -= c[ways[i][end]];
        end++;
      }
      
      if(score == k) {
        best = max(best,start - end + 1);
      }
    }
  }
  
  sort(islands.begin(),islands.end(),[](island a, island b) -> bool {
    return a.value < b.value;
  });
  
  vector<vector<island>> is(1,{islands[0]});
  
  for(int i = 1; i < islands.size();i++) {
    if(islands[i].value == islands[i-1].value) {
      is.back().push_back(islands[i]);
    } else{
      is.push_back({islands[i]});
    }
  }
  
  int left = 0;
  int right = is.size()-1;
  
  int goal = k - c[0];
  
  while(left <= right) {
    if(is[left][0].value + is[right][0].value < goal) {
      left++;
    } 
    else if(is[left][0].value + is[right][0].value > goal) {
      right--;
    } 
    else {
      for(auto i1 : is[left]) {
        for(auto i2 : is[right]) {
          if(i1.way != i2.way && i1.value + i2.value == goal) {
            best = max(best,i1.position + i2.position + 1);
          }
        }
      }
      left++;
      right--;
    }
  }
  
  cout << best << endl;
}

signed main() {
  
  int t;
  cin >> t;
  
  while(t--) 
    solve();
}
