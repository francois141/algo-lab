#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/bipartite.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/connected_components.hpp>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef int Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;

typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;

typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef CGAL::Point_2<K> Point;

typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::undirectedS> graph;


using namespace std;

#define int long

void solve() {
  
  int n,m,r;
  cin >> n >> m >> r;
  
  vector<pair<Point,Index>> radios(0);
  vector<pair<Point,Point>> clues(0);
  
  for(int i = 0; i < n;i++) {
    int x,y;
    cin >> x >> y;
    radios.push_back(make_pair(Point(x,y),i));
  }
  
  for(int i = 0; i < m;i++) {
    int x,y,z,t;
    cin >> x >> y >> z >> t;
    clues.push_back(make_pair(Point(x,y),Point(z,t)));
  }
  
  graph G(n);
  
  Triangulation t;
  t.insert(radios.begin(),radios.end());
  
  for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    if(t.segment(e).squared_length() <= r*r) {
        boost::add_edge(i1,i2,G);
    }
  }
  
  bool is_bipartite = boost::is_bipartite(G);

  vector<int>component(num_vertices(G));
  boost::connected_components(G, &component[0]);
  
  for(int i = 0; i < m;i++) {
    
    auto p1 = clues[i].first;
    auto p2 = clues[i].second;
    
    if(!is_bipartite) {
      cout << "n";
      continue;
    }
    
    if(CGAL::squared_distance(p1,p2) <= r*r) {
      cout << "y";
      continue;
    }
    
    auto n1 = t.nearest_vertex(p1);
    auto n2 = t.nearest_vertex(p2);
    
    if(CGAL::squared_distance(p1,n1->point()) > r*r || CGAL::squared_distance(p2,n2->point()) > r*r) {
      cout << "n";
      continue;
    }
    
    if(component[n1->info()] == component[n2->info()]) {
      cout << "y";
    }
    else {
      cout << "n";
    }
  }
  cout << "\n";
}


signed main() {
  int t; cin >> t;
  
  while(t--) {
    solve();
  }
  return 0;
}
