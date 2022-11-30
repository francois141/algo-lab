#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K; 
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;

typedef CGAL::Point_2<K> Point;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;    
typedef boost::graph_traits<graph>::edge_iterator edge_it; 

using namespace std;

#define int long

void solve() {
  
  int n,r;
  cin >> n >> r;
  
  vector<pair<Point,int>> positions(n);
  for(int i = 0; i < n;i++) {
    int x,y;
    cin >> x >> y;
    positions[i] = make_pair(Point(x,y),i);
  }

  int start = 1;
  int end = n;
  
  while(start != end) {
  
    int middle = (start + end + 1) / 2;
    
    Triangulation t;
    t.insert(positions.begin() + middle, positions.end());
    
    int currentSize = n - middle;
    
    graph G(currentSize);
    
    for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
      int u = e->first->vertex((e->second+1)%3)->info();
      int v = e->first->vertex((e->second+2)%3)->info();
      if(t.segment(e).squared_length() <= r*r) {
        boost::add_edge(u - middle,v - middle,G);
      }
    }
    
    vector<int> component_map(currentSize);
    int ncc = boost::connected_components(G, &component_map[0]);
    
    int biggest = 0;
    vector<int> compSize(currentSize,0);
    for(int i = 0; i < currentSize;i++) {
      int c = component_map[i];
      compSize[c]++;
      biggest = max(biggest,compSize[c]);
    } 
    
    if(middle <= biggest) {
      start = middle;
    }
    else {
      end = middle-1;
    }
  }
  
  cout << start << endl;
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
