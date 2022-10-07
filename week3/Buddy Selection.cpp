#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

using namespace std;

void solve() {
  
  int n,c,f;
  cin >> n >> c >> f;
  
  vector<set<string>> car = vector<set<string>>(n,set<string>());
  
  for(int i = 0; i < n;i++) {
    for(int j = 0; j < c;j++) {
      string s;
      cin >> s; 
      car[i].insert(s);
    }
  }
  
  graph G(n);
  
  for(int i = 0; i < n;i++) {
    for(int j = 0; j < i;j++) {
      vector<string> intersection;
      set_intersection(car[i].begin(),car[i].end(),car[j].begin(),car[j].end(),back_inserter(intersection));
      if(intersection.size() > f) {
        boost::add_edge(i,j,G);
      }
    }
  }
  
  vector<vertex_desc> mate_map(n);
  
  boost::edmonds_maximum_cardinality_matching(G,boost::make_iterator_property_map(mate_map.begin(),boost::get(boost::vertex_index,G)));
  
  int matching_size = boost::matching_size(G,boost::make_iterator_property_map(mate_map.begin(),boost::get(boost::vertex_index,G)));
  
  if(2*matching_size == n)  {
    cout << "not optimal\n";
  } else {
    cout << "optimal\n";
  }
  
  return;
}

int main() {
  
  int t;
  cin >> t;
  
  while(t--) 
    solve();
  
}
