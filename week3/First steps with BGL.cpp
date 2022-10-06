#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t,int>> graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_descriptor;
typedef boost::property_map<graph,boost::edge_weight_t>::type edge_weights;

int mst_size(graph &G) {
  
  vector<edge_descriptor> mst(0);
  
  boost::kruskal_minimum_spanning_tree(G,back_inserter(mst));
  
  edge_weights e = get(boost::edge_weight, G);
  
  unsigned int sum = 0;
  for(auto it = mst.begin();it != mst.end(); ++it) {
    sum += e[*it];
  }
  
  return sum;
}

int dist_max(graph &G) {
  
  int n = boost::num_vertices(G);
  
  vector<int> d(n); 
    
  boost::dijkstra_shortest_paths(G,0,boost::distance_map(boost::make_iterator_property_map(d.begin(),boost::get(boost::vertex_index,G))));
  
  return *max_element(d.begin(),d.end());
}

void solve() {
  int n,m;
  cin >> n >> m;
  
  graph G(n);
  
  for(int i = 0; i < m;i++) {
    int a,b,c;
    cin >> a >> b >> c;
    add_edge(a,b,c,G);
  }
  
  cout << mst_size(G) << " " << dist_max(G) << "\n";
  return;
}

int main() {
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
