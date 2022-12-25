#include <bits/stdc++.h>

#define int long

using namespace std;

struct Spec {
  string name;
  int age;
};

struct Query {
  int max_age;
  int idx;
};

vector<vector<int>> graph;
vector<bool> isChild;
vector<vector<Query>> queries;
vector<int> solutions;
vector<Spec> species;

vector<int> path; 
vector<int> ages;

void dfs(int idx) {
  path.push_back(idx);
  ages.push_back(species[idx].age);
  
  for(auto q: queries[idx]) {
    auto low = std::lower_bound(ages.begin(), ages.end(), q.max_age, std::greater<int>());
    solutions[q.idx] = path[low-ages.begin()];
  }
  
  for(auto c: graph[idx]) dfs(c);
  
  path.pop_back();
  ages.pop_back();
}

void solve() {
   
  int n,q;
  cin >> n >> q;

  map<string,int> conv;
  
  species = vector<Spec>(n);
  for(int i = 0; i < n;i++) {
    string name;
    int age;
    cin >> name >> age;
    species[i] = Spec{name,age};
    conv[species[i].name] = i;
  }
  
  graph = vector<vector<int>>(n,vector<int>(0));
  isChild = vector<bool>(n,false);
  
  for(int i = 0; i < n-1;i++) {
    string a,b;
    cin >> a >> b;
    int from = conv[b];
    int to = conv[a];
    graph[from].push_back(to);
    isChild[to] = true;
  }
  
  int root = 0; 
  for(int i = 0; i < n;i++) {
    if(!isChild[i]) {
      root = i;
    }
  }
  
  queries = vector<vector<Query>>(n, vector<Query>(0));
  solutions = vector<int>(q);
  
  for(int i = 0; i < q;i++) {
    string name; int age;
    cin >> name >> age;
    int idx = conv[name];
    queries[idx].push_back(Query{age,i});
  }
  
  path = vector<int>(0);
  ages = vector<int>(0);
  
  dfs(root);
  
  for(auto ans: solutions) {
    cout << species[ans].name << " ";
  }
    
  cout << endl; 
}

signed main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
