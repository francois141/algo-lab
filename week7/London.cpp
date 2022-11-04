#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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
  
  int h,w;
  cin >> h >> w;
  
  string n;
  cin >> n;
  
  vector<string> front(h);
  vector<string> back(h);
  
  for(int i = 0; i < h;i++)
    cin >> front[i];
    
  for(int i = 0; i < h;i++)
    cin >> back[i];
  
  vector<int> letters(26,0);
  for(char c : n) 
    letters[c - 'A']++;
  
  graph G(26*26 + 26);
  edge_adder adder(G);
  
  vertex_desc v_source = boost::add_vertex(G);
  vertex_desc v_sink = boost::add_vertex(G);

  vector<vector<int>> letterMatrix(26,vector<int>(26,0));
  
  for(int i = 0; i < h;i++) {
    for(int j = 0; j < w;j++) {
      const int idx1 = front[i][j] - 'A';
      const int idx2 = back[i][w-j-1] - 'A'; 
      letterMatrix[idx1][idx2]++;
    }
  }
    
  const int offset = 26*26;
  
  for(int i = 0; i < 26;i++) {
    for(int j = 0; j < 26;j++) {
      if(letterMatrix[i][j] != 0) {
        int idx = i*26 + j;
        adder.add_edge(v_source,idx,letterMatrix[i][j]);
        adder.add_edge(idx,offset+i,letterMatrix[i][j]);
        adder.add_edge(idx,offset+j,letterMatrix[i][j]);
      }
    }
  }

  for(int i = 0; i < 26;i++) {
    adder.add_edge(offset + i, v_sink, letters[i]);
  }
  
  int flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  
  if(flow == n.size()) {
    cout << "Yes" << "\n";
  }
  else {
    cout << "No" << "\n";
  }

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
