#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

using namespace std;

namespace boost
{
  struct edge_component_t
  {
    enum
    { num = 555 };
    typedef edge_property_tag kind;
  }
  edge_component;
}

typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::undirectedS,boost::no_property,boost::property<boost::edge_component_t,int>> graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_descriptor;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_descriptor;

void solve() {
  
  int n,m;
  cin >> n >> m;
  
  graph G(n);
  
  for(int i = 0; i < m;i++) {
    int a,b;
    cin >> a >> b;
    boost::add_edge(a,b,G);
  }
  
  boost::property_map<graph,boost::edge_component_t>::type component = boost::get(boost::edge_component,G);
  int nums_components = biconnected_components(G,component);

  vector<vector<edge_descriptor>> connections(nums_components,vector<edge_descriptor>(0));
  
  boost::graph_traits<graph>::edge_iterator ei, ei_end;
  for (boost::tie(ei, ei_end) = edges(G); ei != ei_end; ++ei) {
    connections[component[*ei]].push_back(*ei);
  }
  
  vector<pair<int,int>> results(0);
  
  for(int i = 0; i < nums_components;i++) {
    if(connections[i].size() == 1) {
      int u = boost::source(connections[i][0],G);
      int v = boost::target(connections[i][0],G);
      results.push_back(make_pair(min(u,v),max(u,v)));
    }
  }
  
  sort(results.begin(),results.end(),[](pair<int,int> const &a, pair<int,int> const &b) -> bool {
    return a.first < b.first || (a.first == b.first && a.second < b.second);
  });
  
  cout << results.size() << "\n";
  for(auto e : results) {
    cout << e.first << " " << e.second << "\n";
  }
  
  return;
}

int main() {
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
 
}
