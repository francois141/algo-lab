#include <bits/stdc++.h>

#define int long

using namespace std;

struct Edge {
  int to;
  int time;
};

struct Vertex {
  int t;
  int s;
};

vector<int> g;
vector<vector<Edge>> graph;
vector<Vertex> ver;

int totalValue;
int timeSpent;

void traverse(int idx) {
  ver[idx].t = 0;
  ver[idx].s = 1;
  
  for(Edge e : graph[idx]) {
    traverse(e.to);
    ver[idx].t += 2*e.time + ver[e.to].t;
    ver[idx].s += ver[e.to].s;
  }
  
  sort(graph[idx].begin(),graph[idx].end(),[](const Edge &e1, const Edge &e2) -> bool {
    int lost1 = ver[e1.to].s * (ver[e2.to].t + 2*e2.time);
    int lost2 = ver[e2.to].s * (ver[e1.to].t + 2*e1.time);
    return lost2 < lost1;
  });
}

void traverse2(int idx) {
  totalValue -= timeSpent; 
  
  for(Edge e : graph[idx]) {
    timeSpent += e.time; 
    traverse2(e.to);
    timeSpent += e.time; 
  }
}


void solve() {
  int n; cin >> n;
  
  g = vector<int>(n+1,0l);
  for(int i = 1; i <= n;i++) cin >> g[i];
  
  graph = vector<vector<Edge>>(n+1,vector<Edge>(0));
  for(int i = 0; i < n;i++) {
    int u,v,l;
    cin >> u >> v >> l;
    graph[u].push_back({v,l});
  }
  
  ver = vector<Vertex>(n+1);
  
  timeSpent = 0;
  totalValue = accumulate(g.begin(),g.end(),0l);
  
  traverse(0);
  traverse2(0);
  
  cout << totalValue << "\n";
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t; cin >> t;
  
  while(t--)
    solve();
}
