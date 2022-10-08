#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::undirectedS,boost::no_property,boost::property<boost::edge_weight_t,int>> graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_descriptor;
typedef boost::property_map<graph,boost::edge_weight_t>::type edge_weights;

int shortest_path(int from, int to, graph &G) {
  
  vector<int> dist(boost::num_vertices(G));
  
  boost::dijkstra_shortest_paths(G,from,boost::distance_map(boost::make_iterator_property_map(dist.begin(),boost::get(boost::vertex_index,G))));
  
  return dist[to];
}

void solve() {
  
  int n,e,s,a,b;
  cin >> n >> e >> s >> a >> b;
  
  vector<graph> networks = vector<graph>(s,graph(n));
  
  for(int i = 0; i < e;i++) {
    int from,to;
    cin >> from >> to;
    for(int j = 0; j < s;j++) {
      int value;
      cin >> value;
      boost::add_edge(from,to,value,networks[j]);
    }
  }
  
  for(int i = 0; i < s;i++) {
    int tmp;
    cin >> tmp;
  }
  
  graph new_network(n);
  
  for(int i = 0; i < s;i++) {
    vector<edge_descriptor> vertices(0);
    boost::kruskal_minimum_spanning_tree(networks[i],back_inserter(vertices));
    edge_weights e = get(boost::edge_weight,networks[i]);
    
    for(auto tmp : vertices) {
      boost::add_edge(boost::source(tmp,networks[i]),boost::target(tmp,networks[i]),e[tmp],new_network);
    }
  }
  
  cout << shortest_path(a,b,new_network) << "\n";
  return;
}

int main() {
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
