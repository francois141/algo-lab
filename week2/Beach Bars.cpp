#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;


void solve() {
  
  int n;
  cin >>n;
  
  vector<int> a(n);
  for(int i = 0; i < n;i++) 
    cin >> a[i];
    
  sort(a.begin(),a.end());
  
  int score = 0;
  int start = -1;
  int end = 0;
  
  int max_score = INT_MIN;
  int left = 0;
  int right = 0;
  
  vector<int> solutions(0);
  int max_distance = 101;
  
  while(start != n - 1) {
    
    start++;
    score++;
    
    while(end < start && a[start] - a[end] > 200) {
      end++;
      score--;
    }
    
    bool c1 = score > max_score;
    bool c2 = score == max_score && (a[start] - a[end] + 1) / 2  < max_distance;
    
    if(c1 || c2) {
      max_score = score;
      left = end;
      right = start;
      
      max_distance = (a[start] - a[end] + 1) / 2;
      solutions = vector<int>(0);
      
      if((a[start] - a[end]) % 2 == 1) 
        solutions.push_back(a[end] + (a[start]-a[end]) / 2);
      
      solutions.push_back(a[end] + (a[start]-a[end]+1) / 2);
    }

    else if(score == max_score && (a[start] - a[end] + 1) / 2  == max_distance) {
      if((a[start] - a[end]) % 2 == 1) {
        solutions.push_back(a[end] + (a[start]-a[end]) / 2);
      }
      
      solutions.push_back(a[end] + (a[start]-a[end]+1) / 2);
    }
  }
  
  cout << max_score << " " << (a[right] - a[left] + 1) / 2 << "\n";
  
  for(auto e : solutions) {
    cout << e << " ";
  } 
  cout << "\n";
  
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
