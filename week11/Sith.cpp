#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

#define int long

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;

typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::undirectedS> graph;

typedef CGAL::Point_2<K> Point;

using namespace std;

int n,r;
vector<pair<Point,int>> planets;

int testSize(int middle) {
  Triangulation t;
  t.insert(planets.begin() + middle, planets.end());
  
  graph G(n - middle);
  
  for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    if(t.segment(e).squared_length() <= r*r) {
      auto idx1 = e->first->vertex((e->second + 1) % 3)->info() - middle;
      auto idx2 = e->first->vertex((e->second + 2) % 3)->info() - middle;
      boost::add_edge(idx1,idx2,G);
    }
  }
  
  vector<int> component(n-middle);
  boost::connected_components(G,&component[0]);

  vector<int> size(n-middle,0);
  for(auto c : component) size[c]++;

  return *max_element(size.begin(),size.end());
}

void solve() {
  cin >> n >> r;
  
  planets = vector<pair<Point,int>>(n);
  for(int i = 0; i < n;i++) {
    int x,y;
    cin >> x >> y;
    planets[i] = make_pair(Point(x,y),i);
  }
  
  int start = 0;
  int end = planets.size();
  
  while(start != end) {
    int middle = (start + end + 1) / 2;
    if(testSize(middle) >= middle) {
      start = middle;
    } else {
      end = middle-1;
    }
  }
  
  cout << start << "\n";
}

signed main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
