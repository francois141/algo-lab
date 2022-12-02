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

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

void solve() {
  
  int b,s,p;
  cin >> b >> s >> p;
  
  vector<vector<pair<int,int>>> pairs(b,vector<pair<int,int>>(0));
  for(int i = 0; i < p;i++) {
    int bi,si,pi;
    cin >> bi >> si >> pi;
    pairs[bi].push_back(make_pair(si,50-pi));
  }
  
  graph G(b+s);

  edge_adder adder(G);
  
  auto v_source = boost::add_vertex(G);
  auto v_sink = boost::add_vertex(G);

  for(int i = 0; i < pairs.size();i++) {
    for(int j = 0; j < pairs[i].size();j++) {
      auto e = pairs[i][j];
      adder.add_edge(i,b+e.first,1,e.second);
    }
  }
  
  for(int i = 0; i < b;i++) {
    adder.add_edge(v_source,i,1,0);
    adder.add_edge(i,v_sink,1,50);
  }
  for(int i = 0; i < s;i++) {
    adder.add_edge(b+i,v_sink,1,0);
  }
  
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  int cost = boost::find_flow_cost(G);
  
  cout << 50*b - cost << "\n";
}

int main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
    
  int t; cin >> t;
  
  while(t--)
    solve();
  
  return 0;
}
