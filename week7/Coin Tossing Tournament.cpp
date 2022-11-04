#include <iostream>
#include <vector>
#include <numeric>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;

#define int long 

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
  
  vector<pair<int,int>> players(m);
  vector<int> outcomes(m);
  vector<int> scores(n);
  
  for(int i = 0; i < m;i ++) {
    int a,b;
    cin >> a >> b;
    players[i] = make_pair(a,b);
    cin >> outcomes[i];
  }
  
  for(int i = 0; i < n;i++) {
    cin >> scores[i];
  }
  
  if(accumulate(scores.begin(),scores.end(),0) != m) {
    cout << "no" << "\n"; 
    return;
  }
  
  graph G(n + m);
  edge_adder adder(G);
  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);

  for(int i = 0; i < m;i++) {
    if(outcomes[i] == 0) {
      adder.add_edge(i,m + players[i].first,1);
      adder.add_edge(i,m + players[i].second,1);
    }
    else if(outcomes[i] == 1) {
      scores[players[i].first]--;
      if(scores[players[i].first] < 0) {
        cout << "no" << "\n";
        return;
      }
    }
    else if(outcomes[i] == 2) {
      scores[players[i].second]--;
      if(scores[players[i].second] < 0) {
        cout << "no" << "\n";
        return;
      }
    }
  }
  
  for(int i = 0; i < m;i++) {
    adder.add_edge(v_source, i ,1);
  }
  
  for(int i = 0; i < n;i++) {
    adder.add_edge(m + i, v_sink, scores[i]);
  }

  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  long value = accumulate(scores.begin(),scores.end(),0);
  
  cout << ((flow == value) ? "yes" : "no") << "\n";
  
  return;
}

signed main() {
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
