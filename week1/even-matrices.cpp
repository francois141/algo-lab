#include <iostream>
#include <vector>

using namespace std;

void solve() {
  
  int n;
  cin >> n;
  n++;
  
  vector<vector<int>> matrix = vector<vector<int>>(n,vector<int>(n,0));
  
  for(int i = 1; i < n;i++) {
    for(int j = 1; j < n;j++) {
      cin >> matrix[i][j];
    }
  }
  
  for(int i = 1; i < n;i++) {
    matrix[i][0] += matrix[i-1][0];
    matrix[0][i] += matrix[0][i-1];
  }
  
  unsigned int count = 0;
  
  for(int i = 1; i < n;i++) {
    for(int j = 1; j < n;j++) {
      matrix[i][j] += matrix[i-1][j] + matrix[i][j-1] - matrix[i-1][j-1];
    }
  }
  
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < i; j++) {
      unsigned int evens = 0;
      unsigned int odds = 0;
      for(int k = 0; k < n; k++) {
        (matrix[i][k]-matrix[j][k]) % 2 == 0 ? evens++ : odds++;
      }
      count += (evens*(evens-1) + odds*(odds-1)) / 2;
    }
  }
  
  cout << count << "\n";
  
}

int main() {
  
  int t; 
  cin >> t;
  
  while(t--) {
    solve();
  }
  
}
