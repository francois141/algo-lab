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

typedef struct Point {
  int x;
  int y;
} Point;

void solve() {
  
  int column,row,k,c;
  cin >> column >> row >> k >> c;
  
  vector<Point> positions(k);
  for(int i = 0; i < k;i++) {
    int x,y; cin >> x >> y;
    positions[i] = {x,y};
  }

  if(column*row == 0) {
    cout << 0 << "\n";
    return;
  }

  graph G(2*column*row);
  edge_adder adder(G);
  
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  const int size = row * column;
  
  // Add bind in and out in intersections
  for(int i = 0; i < row*column;i++) {
    adder.add_edge(i,i+size,c);
  }
  
  // Bind corridors with intersections
  for(int i = 0; i < row-1;i++) {
    for(int j = 0; j < column;j++) {
      const int i1 = i*column + j;
      const int i2 = (i+1)*column + j;
      adder.add_edge(i1 + size, i2, 1);
      adder.add_edge(i2 + size, i1, 1);
    }
  }
  
  for(int j = 0; j < row;j++) {
    for(int i = 0; i < column-1;i++) {
      const int i1 = j*column + i;
      const int i2 = j*column + i + 1;
      adder.add_edge(i1 + size, i2, 1);
      adder.add_edge(i2 + size, i1, 1);
    }
  }
  
  // Bind corridors with sink
  for(int i = 0; i < row;i++) {
    adder.add_edge(i*column + size,v_sink,1);
    adder.add_edge(i*column + column-1 + size,v_sink,1);
  }
  
  for(int i = 0; i < column;i++) {
    adder.add_edge(i + size,v_sink,1);
    adder.add_edge(column*(row-1) + i + size,v_sink,1);
  }
  
  // Bind starting points for knights
  for(int i = 0; i < k;i++) {
    adder.add_edge(v_source,positions[i].y * column + positions[i].x,1); 
  }
  
  // Get the max flow & output it
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  cout << flow << "\n";
  
  return;
}

signed main() {
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
    
  return 0;
}
