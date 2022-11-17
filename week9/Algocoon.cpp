#include <iostream>
#include <vector>
#include <numeric>

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
    
    void add_edge(int from, int to, int weight) {
      auto c_map = boost::get(boost::edge_capacity, G);
      auto r_map = boost::get(boost::edge_reverse, G);
      const auto e = boost::add_edge(from, to, G).first;
      const auto rev_e = boost::add_edge(to, from, G).first;
      c_map[e] = weight;
      c_map[rev_e] = 0; 
      r_map[e] = rev_e;
      r_map[rev_e] = e;
    }
}; 

void solve() {
  
  int n,m;
  cin >> n >> m;
  
  graph G(n);
  edge_adder adder(G);
  
  for(int i = 0; i < m;i++) {
    int a,b,c;
    cin >> a >> b >> c;
    adder.add_edge(a,b,c);
  }
  
  long min_cut = LONG_MAX;
  
  for(int i = 0; i < n;i++) {
      long flow = boost::push_relabel_max_flow(G, 0, i);
      min_cut = min(min_cut,flow);
      
      flow =  boost::push_relabel_max_flow(G,i, 0);
      min_cut = min(min_cut,flow);
  }
  
  cout << min_cut << "\n";

  
  return;
}

signed main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
