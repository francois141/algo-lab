///4
#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      graph;

using namespace std;

int dijkstra_dist(const graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}


void solve() {
  int n,m,k,x,y;
  cin >> n >> m >> k >> x >> y;
  
  graph G(n*(k+1));
  
  for(int i = 0; i < m;i++) {
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    
    for(int j = 0; j <= k; j++) {
      boost::add_edge(j*n+a ,min(j+d,k)*n + b,c,G);
      boost::add_edge(j*n+b ,min(j+d,k)*n + a,c,G);
    }
  }
  
  cout << dijkstra_dist(G,x,k*n + y) << "\n";
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
