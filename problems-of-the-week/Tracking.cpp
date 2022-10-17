#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::undirectedS,boost::no_property,boost::property<boost::edge_weight_t,int>> graph;

int compute(const graph &G, int from, int to) {
  
  vector<int> distances(boost::num_vertices(G));
  
  boost::dijkstra_shortest_paths(G,from,boost::distance_map(boost::make_iterator_property_map(distances.begin(),boost::get(boost::vertex_index,G))));

  return distances[to];
}

void solve() {
  
  int n,m,k,x,y;
  cin >> n >> m >> k >> x >> y;
  
  graph G(n*(k+1));
  
  for(int i = 0; i < m;i++) {
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    
    for(int i = 0; i < k;i++) {
      boost::add_edge(a + n*i,b + n*(i+d),c,G);
      boost::add_edge(a + n*(i+d),b + n*i,c,G);
    }
    
    boost::add_edge(a + n*k,b + n*k,c,G);
  }
  
  cout << compute(G,x,n*k + y) << "\n";
  
  return;
}

int main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
