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
      c_map[rev_e] = 0; 
      r_map[e] = rev_e;
      r_map[rev_e] = e;
    }

}; 

int w,h;

int flatten(int i, int j) {
  return i * w + j;
}


void solve() {
  
  cin >> w >> h;
  
  vector<string> grid(h);
  
  for(int i = 0; i < h;i++) {
    cin >> grid[i];
  }
  
  graph G(w*h);
  edge_adder adder(G);
  
  vertex_desc v_source = boost::add_vertex(G);
  vertex_desc v_sink = boost::add_vertex(G);
  
  int counter = 0;
  
  for(int i = 0; i < h;i++) {
    for(int j = 0; j < w;j++) {
      
      if(grid[i][j] == 'x') continue;
      
      counter++;
      
      if((i + j) % 2 == 0) {
        adder.add_edge(v_source,flatten(i,j));
        if(i > 0) adder.add_edge(flatten(i,j),flatten(i-1,j));
        if(i < h-1) adder.add_edge(flatten(i,j),flatten(i+1,j));
        if(j > 0) adder.add_edge(flatten(i,j),flatten(i,j-1));
        if(j < w-1) adder.add_edge(flatten(i,j),flatten(i,j+1));
      }
      else {
        adder.add_edge(flatten(i,j),v_sink); 
      }
    }
  }
  
  int flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  
  if(2*flow == counter) {
    cout << "yes" << "\n";
  }
  else {
    cout << "no" << "\n";
  }

  return;
}

signed main() {
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
