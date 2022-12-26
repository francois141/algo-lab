#include <bits/stdc++.h>

using namespace std;

struct Spec {
  string name;
  int age;
};

struct Query {
  int max_age;
  int idx;
};

struct Path {
  int index;
  int age;
};

vector<vector<int>> graph;
vector<vector<Query>> queries;
vector<int> solutions;
vector<Spec> species;

vector<Path> path; 

void dfs(int idx) {
  path.push_back({idx, species[idx].age});
  
  for(auto q: queries[idx]) solutions[q.idx] = std::lower_bound(path.begin(), path.end(), Path{0,q.max_age}, [](Path a, Path b) {
    return a.age > b.age; 
  })->index;
  
  for(auto c: graph[idx]) dfs(c);
  
  path.pop_back();
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
  vector<bool> isChild = vector<bool>(n,false);
  
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
      break;
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
  
  path = vector<Path>(0);

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
