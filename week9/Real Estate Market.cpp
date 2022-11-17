#include <iostream>

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

void solve() {
  
  const int NO_COST = 0;
  
  int N,M,S;
  cin >> N >> M >> S;
  
  vector<int> limits(S);
  for(int i = 0; i < S; i++) {
    cin >> limits[i];
  }
  
  vector<int> group(M);
  for(int i = 0; i < M;i++) {
    cin >> group[i];
    group[i]--;
  }
  
  vector<vector<int>> bets(N,vector<int>(M,0));
  
  int max_bet = 0;
  
  for(int i = 0; i < N;i++) {
    for(int j = 0; j < M;j++) {
      cin >> bets[i][j]; 
      max_bet = max(max_bet,bets[i][j]); 
    }
  }
  
  graph G(N + M + S);
  edge_adder adder(G);  
  
  vertex_desc v_source = boost::add_vertex(G);
  vertex_desc v_sink = boost::add_vertex(G);
  
  for(int i = 0; i < N;i++) {
    adder.add_edge(v_source,i,1,NO_COST);
  }
  
  for(int i = 0; i < N;i++) {
    for(int j = 0; j < M;j++) {
      adder.add_edge(i,N + j,1,max_bet-bets[i][j]);
    }
  }
  
  for(int j = 0; j < M;j++) {
    adder.add_edge(N + j,N + M + group[j],1,NO_COST);
  }
  
  for(int i = 0; i < S;i++) {
    adder.add_edge(N + M + i,v_sink,limits[i],NO_COST);
  }

  int flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  int cost = boost::find_flow_cost(G);
  
  cout << flow << " " << max_bet*flow-cost << "\n";
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
