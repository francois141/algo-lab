#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

#define int long

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
  int h,w;
  cin >> h >> w;
  
  string s;
  cin >> s;
  
  vector<int> count(26,0);
  for(int i = 0; i < s.size();i++) {
    count[s[i] - 'A']++; 
  }
  
  vector<string> sfront(h);
  vector<string> sback(h);
  
  for(int i = 0; i < h;i++) {
    cin >> sfront[i];
  }
  for(int i = 0; i < h;i++) {
    cin >> sback[i];
  }
  
  vector<vector<int>> matrix(26,vector<int>(26,0));
  
  for(int i = 0; i < h;i++) {
    for(int j = 0; j < w;j++) {
      matrix[sfront[i][j] - 'A'][sback[i][w - j - 1] - 'A']++;
    }
  }
  
  graph G(26*26 + 26);
  edge_adder adder(G);
  
  auto v_source = boost::add_vertex(G);
  auto v_sink = boost::add_vertex(G);
  
  for(int i = 0; i < 26;i++) {
    for(int j = 0; j < 26;j++) {
      adder.add_edge(v_source,26*i + j, matrix[i][j]);
      adder.add_edge(26*i + j, 26*26 + i,INT_MAX); 
      adder.add_edge(26*i + j, 26*26 + j,INT_MAX); 
    }
  }

  for(int k = 0; k < 26; k++) {
    adder.add_edge(26*26 + k, v_sink, count[k]);
  }
  
  long flow = boost::push_relabel_max_flow(G,v_source,v_sink);
  
  if(flow == s.size())  {
    cout << "Yes" << "\n";
  } else {
    cout << "No" << "\n";
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
