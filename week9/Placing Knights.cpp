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

vector<vector<int>> grid;

class edge_adder {
  
  graph &G;
  int n;
  
  public:
    explicit edge_adder(graph &G, int n) : G(G), n(n) {}
    
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
  
  int n;
  cin >> n;
  
  vector<vector<int>> grid = vector<vector<int>>(n,vector<int>(n));
  
  int nb_placements = 0;
  
  graph G(n*n);
  edge_adder adder(G,n);
  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  vector<pair<int,int>> displacements = {{-1,-2},{-1,2},{1,-2},{1,2},{-2,-1},{-2,1},{2,-1},{2,1}};
  
  for(int i = 0; i < n;i++) {
    for(int j = 0; j < n;j++) {
    
      cin >> grid[i][j];
      
      if(grid[i][j]) {
        nb_placements++;
        if((i + j) % 2 == 0) {
          adder.add_edge(v_source,i*n+j,1);
        }
        else {
          adder.add_edge(i*n+j,v_sink,1);
        }
      }
    }
  }
  
  for(int i = 0; i < n;i++) {
    for(int j = 0; j < n;j++) {
      if(grid[i][j] && (i+j) % 2 == 0) {
        for(auto d : displacements) {
          if(i+d.first < 0 || i+d.first >= n) continue;
          if(j+d.second < 0 || j+d.second >= n) continue;
          adder.add_edge(i*n+j,(i+d.first)*n + j + d.second,1);
        }        
      }
    }
  }
  
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  
  cout << nb_placements - flow << "\n";
  
  return;
}

signed main() {
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
