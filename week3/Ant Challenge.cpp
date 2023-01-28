#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#define int long 

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      graph;
typedef boost::property_map<graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor          vertex_desc;

int dijkstra_dist(const graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}

void solve() {
  int n,e,s,a,b;
  cin >> n >> e >> s >> a >> b;
  
  vector<graph> networks(s,graph(n));
  for(int i = 0; i < e;i++) {
    int from,to;
    cin >> from >> to;
    for(int j = 0; j < s;j++) {
      int w;
      cin >> w;
      boost::add_edge(from,to,w,networks[j]);
    }
  }
  
  int tmp;
  for(int i = 0; i < s; i++) cin >> tmp;
  
  graph final(n);
  
  for(auto net : networks) {
    std::vector<edge_desc> mst;
    boost::kruskal_minimum_spanning_tree(net, std::back_inserter(mst));
    
    auto weights = boost::get(boost::edge_weight,net);
    
    for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
      boost::add_edge(boost::source(*it, net),boost::target(*it, net),weights[*it],final);
    }
  }
  
  cout << dijkstra_dist(final,a,b) << endl;
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
    
  return 0;
}
