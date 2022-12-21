#include <bits/stdc++.h>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      graph;
  
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property> graph_undirected;
typedef boost::graph_traits<graph_undirected>::vertex_descriptor vertex_desc_undirected;

using namespace std;

int n,m,a,s,c,d;
vector<vector<int>> dist_map;
vector<int> agents;
vector<int> shelters;

bool valid(int distance) {
 
  graph_undirected G(a + s*c);
  
  int asize = agents.size();
  int ssize = shelters.size();
  
  for(int i = 0; i < asize; i++) {
    for(int j = 0; j < ssize; j++) {
      
      int aindex = agents[i];
      int sindex = shelters[j];
    
      if(dist_map[aindex][sindex] == INT_MAX)
        continue;
      
      if(dist_map[aindex][sindex] + d <= distance)
        boost::add_edge(i,asize + j,G);
      if(c == 2 && dist_map[aindex][sindex] + 2*d <= distance) 
        boost::add_edge(i,asize+ssize+j,G);
    }
  }
  
  int size = boost::num_vertices(G);
  std::vector<vertex_desc_undirected> mate_map(size); 
 
  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
    
  return matching_size == asize;
}

void solve() {
  
  cin >> n >> m >> a >> s >> c >> d;
  
  graph G(n);
  
  for(int i = 0; i < m;i++) {
    char w;
    int x,y,z;
    cin >> w >> x >> y >> z;

    if(w == 'S') {
      boost::add_edge(x,y,z,G);
    }
    if(w == 'L') {
      boost::add_edge(x,y,z,G);
      boost::add_edge(y,x,z,G);
    }
  }
  
  agents = vector<int>(a);
  shelters = vector<int>(s);
  
  for(int i = 0; i < a;i++)  {
    cin >> agents[i];
  }
  for(int i = 0; i < s;i++) {
    cin >> shelters[i];
  } 

  dist_map = vector<vector<int>>(n,vector<int>(n));
  
  for(int from = 0; from < n;from++) {
    boost::dijkstra_shortest_paths(G, from ,boost::distance_map(boost::make_iterator_property_map(
      dist_map[from].begin(), boost::get(boost::vertex_index, G))));
  }

  // Binary search on the solution space
  int start = 0;
  int end = INT_MAX / 2;
  
  while(start < end) {
    int middle = (start + end) / 2;
    if(valid(middle)) {
      end = middle;
    }
    else {
      start = middle+1;
    }
  }
  
  cout << start << endl;
    
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