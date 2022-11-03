#include <iostream>
#include <vector>

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
    
    void add_edge(int from, int to) {
      auto c_map = boost::get(boost::edge_capacity, G);
      auto r_map = boost::get(boost::edge_reverse, G);
      const auto e = boost::add_edge(from, to, G).first;
      const auto rev_e = boost::add_edge(to, from, G).first;
      c_map[e] = 1;
      c_map[rev_e] = 1; 
      r_map[e] = rev_e;
      r_map[rev_e] = e;
    }
}; 

void solve() {
  
  int n,m,s;
  cin >> n >> m >> s;
  
  graph G(n);
  edge_adder adder(G);
  
  const vertex_desc v_sink = boost::add_vertex(G);
  const int v_source = 0;
  
  for(int i = 0; i < s;i++) {
    int store; cin >> store;
    adder.add_edge(store,v_sink);
  }
  
  for(int i = 0; i < m;i++) {
    int part1,part2;
    cin >> part1 >> part2;
    adder.add_edge(part1,part2);
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  
  cout << ((flow == s) ? "yes" : "no") << "\n";
  
  return;
}

int main() {
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
