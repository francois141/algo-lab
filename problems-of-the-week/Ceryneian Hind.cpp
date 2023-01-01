#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;

typedef boost::adjacency_list_traits<boost::vecS,boost::vecS,boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
  boost::property<boost::edge_capacity_t, long,
    boost::property<boost::edge_residual_capacity_t, long,
      boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
      
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

class edge_adder {
  graph &G;
  
  public:
    explicit edge_adder(graph &G) : G(G) {}
    
    void add_edge(int from, int to,int capacity) {
      auto c_map = boost::get(boost::edge_capacity, G);
      auto r_map = boost::get(boost::edge_reverse, G);
      const auto e = boost::add_edge(from, to, G).first;
      const auto rev_e = boost::add_edge(to, from, G).first;
      c_map[e] = capacity;
      c_map[rev_e] = 0; 
      r_map[e] = rev_e;
      r_map[rev_e] = e;
    }
}; 

void solve() {
  
  int n,m;
  cin >> n >> m;
  
  vector<int> scores = vector<int>(n);
  for(int i = 0; i < n;i++) cin >> scores[i];
  
  int sum_positive = accumulate(scores.begin(),scores.end(),0,[](int a, int b) -> int {
    return max(a,0)+max(b,0);
  });
  
  graph G(n);
  edge_adder adder(G);
  
  auto v_source = boost::add_vertex(G);
  auto v_sink = boost::add_vertex(G);
  
  for(int i = 0; i < m;i++) {
    int u,v;
    cin >> u >> v;
    adder.add_edge(u,v,sum_positive);
  }

  for(int i = 0; i < n;i++) {
    if(scores[i] >= 0) {
      adder.add_edge(v_source,i,scores[i]);
    } else {
      adder.add_edge(i,v_sink,abs(scores[i]));
    }
  }
  
  int flow = boost::push_relabel_max_flow(G,v_source,v_sink);
  int ans = sum_positive - flow;
  
  if(ans == 0) {
    cout << "impossible" << "\n";
  } else {
    cout << ans << "\n";
  }
}

int main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t; cin >> t;
  while(t--) 
    solve();
  
  return 0;
}
