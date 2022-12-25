#include <bits/stdc++.h>

using namespace std;

struct Spec {
  string name;
  int age;
};

void solve() {
   
  int n,q;
  cin >> n >> q;

  unordered_map<string,int> conv;
  
  vector<Spec> species;
  species.reserve(n);
  for(int i = 0; i < n;i++) {
    string name;
    int age;
    cin >> name >> age;
    species.push_back({name,age});
    conv[species[i].name] = i;
  }
  
  vector<int> parent(n,-1);
  for(int i = 0; i < n-1;i++) {
    string a,b;
    cin >> a >> b;
    int from = conv[a];
    int to = conv[b];
    parent[from] = to;
  }
  
  int root = -1; 
  for(int i = 0; i < n;i++) {
    if(parent[i] == -1) {
      root = i;
      break;
    }
  }
  
  parent[root] = root;
  
  vector<vector<int>> anc = vector<vector<int>>(n,vector<int>(16));
  
  for(int i = 0; i < n;i++) anc[i][0] = parent[i];
  
  for(int j = 1; j <= 16; j++) {
    for(int i = 0; i < n;i++) { 
      anc[i][j] = anc[parent[i]][j-1]; 
    }
  }
  
  for(int i = 0; i < q;i++) {
    string name; int age;
    cin >> name >> age;
    
    int start = conv[name];
    while(start != root) {
      int idx = -1;
      for(int j = 0; j < anc[start].size();j++) {  
        if(species[anc[start][j]].age <= age) {
          idx = j;
        }
      }
      if(idx == -1) break;
      start = anc[start][idx];
    }

    cout << species[start].name << " ";
  }
  
  cout << "\n"; 
}

int main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
