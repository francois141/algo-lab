#include <bits/stdc++.h>

using namespace std;

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::undirectedS,boost::no_property,boost::property<boost::edge_weight_t,int>> graph;
  
// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph_flow;

// Custom edge adder class, highly recommended
class edge_adder {
  graph_flow &G;

 public:
  explicit edge_adder(graph_flow &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};
  
struct Edge {
  int from;
  int to;
  int width;
  int length;
};

vector<int> dijkstra_dist(const graph &G, int s) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map;
}

  
void solve() {
  
  int n,m,s,f;
  cin >> n >> m >> s >> f;
  
  vector<Edge> edges = vector<Edge>(m);
  for(int i = 0; i < m;i++) {
    cin >> edges[i].from;
    cin >> edges[i].to;
    cin >> edges[i].width;
    cin >> edges[i].length;
  }
  
  graph G(n);
  for(int i = 0; i < m;i++) {
    boost::add_edge(edges[i].from,edges[i].to, edges[i].length, G);
  }
  
  vector<int> dist = dijkstra_dist(G,s);

  graph_flow G_flow(n);
  edge_adder adder(G_flow);
  
  for(auto edge: edges) {
    
    int a = edge.from;
    int b = edge.to;
    int length = edge.length;
    int width = edge.width;
    
    if(dist[a] + length == dist[b]) adder.add_edge(a,b,width);
    if(dist[b] + length == dist[a]) adder.add_edge(b,a,width);
  }
  
  cout << boost::push_relabel_max_flow(G_flow, s, f) << endl;
}

int main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t; cin >> t;
  while(t--)
    solve();
  
  return 0;
}
