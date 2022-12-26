#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; 

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it;
typedef traits::vertex_descriptor vertex_desc;


class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); 
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; 
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   
    w_map[rev_e] = -cost; 
  }
};

struct Match {
  int u;
  int v;
  int r;
};

void solve() {
  
  int e,w,m,d,p,l;
  cin >> e >> w >> m >> d >> p >> l;
  
  vector<Match> matches = vector<Match>(m+d);
  for(int i = 0; i < m + d;i++) {
    cin >> matches[i].u;
    cin >> matches[i].v;
    cin >> matches[i].r;
  }

  graph G(2*(e+w));
  edge_adder adder(G);  
  
  vertex_desc v_source = boost::add_vertex(G);
  vertex_desc v_source_2 = boost::add_vertex(G);
  vertex_desc v_sink = boost::add_vertex(G);
  vertex_desc v_sink_2 = boost::add_vertex(G);
  
  unsigned int offset = e + w;
  unsigned int max_difficulty = 1e4;
  
  // Start
  adder.add_edge(v_source,v_source_2,p - e*l,0);
  for(int i = 0; i < e;i++) adder.add_edge(v_source,i,l,0);
  for(int i = 0; i < e;i++) adder.add_edge(v_source_2,i,INT_MAX,0);
  for(int i = 0; i < e;i++) adder.add_edge(v_source_2,i+offset,INT_MAX,0);
  
  // Middle
  for(int i = 0; i < m;i++) adder.add_edge(matches[i].u, e + matches[i].v, 1, matches[i].r);
  for(int i = m; i < m+d;i++) adder.add_edge(offset + matches[i].u, offset + e + matches[i].v, 1, matches[i].r);
  for(int i = e; i < e + w;i++) adder.add_edge(i, offset + i, INT_MAX, 0);
  
  // End
  for(int i = e; i < e + w;i++) adder.add_edge(i,v_sink,l,0);
  for(int i = e; i < e + w;i++) adder.add_edge(offset + i,v_sink_2,INT_MAX,0);
  
  adder.add_edge(v_sink_2,v_sink,p - w*l,0);
  
  int flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  if(flow != p || p < l*max(e,w)) {
    cout << "No schedule!" << "\n";
  } else {
    boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
    int cost = boost::find_flow_cost(G);
    cout << cost << "\n";
  }
  
  return;
}

int main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
    
  return 0;
}
