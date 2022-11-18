#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                              boost::property<boost::edge_residual_capacity_t, long,
                              boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                              boost::property<boost::edge_weight_t, long>>>>> graph;
                              
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it; 

class edge_adder
{
  graph &G;

public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost)
  {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;      // new assign cost
    w_map[rev_e] = -cost; // new negative cost
  }
};

using namespace std;


void solve()
{
  int n,m,l;
  cin >> n >> m >> l;
  
  const int max_priority = 128;
  
  graph G(n);
  edge_adder adder(G);
    
  auto v_source = boost::add_vertex(G);
  auto v_sink = boost::add_vertex(G);
  
  for(int i = 0; i < n-1;i++) {
    adder.add_edge(i,i+1,l,max_priority);
  }
  
  adder.add_edge(v_source,0,l,0);
  adder.add_edge(n-1,v_sink,l,0);
  
  for(int i = 0; i < m;i++) {
    int x,y,q;
    cin >> x >> y >> q;
    adder.add_edge(x,y,1,max_priority*(y-x)-q);
  }

  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  long flow = boost::find_flow_cost(G);
  flow = l * max_priority * (n - 1) - flow;
  cout << flow << endl;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0); 
  
  int t; 
  cin >> t;
    
  while(t--)
    solve();
    
  return 0;
}
