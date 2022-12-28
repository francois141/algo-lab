#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <boost/pending/disjoint_sets.hpp>

#define int long 

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Triangulation_vertex_base_with_info_2<int,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef CGAL::Point_2<K> Point;

typedef Triangulation::Edge Edge;

using namespace std;

void solve() {
  
  int n,m,s,k;
  cin >> n >> m >> s >> k;
  
  vector<pair<Point,int>> positions = vector<pair<Point,int>>(n);
  vector<pair<Point,int>> bones = vector<pair<Point,int>>(m);
  
  for(int i = 0; i < n;i++) {
    int x,y;
    cin >> x >> y;
    positions[i] = make_pair(Point(x,y),i);
  }
  
  for(int j = 0; j < m;j++) {
    int x,y;
    cin >> x >> y;
    bones[j] = make_pair(Point(x,y),0);
  }
  
  Triangulation t;
  t.insert(positions.begin(),positions.end());
  
  boost::disjoint_sets_with_storage<> uf(n);
  
  for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    auto s1 = e->first->vertex((e->second + 1) % 3);
    auto s2 = e->first->vertex((e->second + 2) % 3);
    if(CGAL::squared_distance(s1->point(),s2->point()) <= s) {
      uf.link(s1->info(),s2->info());
    }
  }
  
  vector<int> values = vector<int>(n,0);
  for(auto bone : bones) {
    Point p = t.nearest_vertex(bone.first)->point();
    int idx = t.nearest_vertex(bone.first)->info();
    if(CGAL::squared_distance(p,bone.first) <= s / 4) {
      values[uf.find_set(idx)]++;
    }
  }
  
  vector<Edge> edges = vector<Edge>(0);

  for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    edges.push_back(*e);
  }
  
  for(int j = 0; j < m;j++) {
    bones[j].second = t.nearest_vertex(bones[j].first)->info();
  }
  
  sort(edges.begin(),edges.end(), [&](auto e1, auto e2) -> bool {
    return t.segment(e1).squared_length() < t.segment(e2).squared_length();
  });
  
  sort(bones.begin(),bones.end(), [&](auto b1, auto b2) -> bool {
    return b1.first < b2.first;
  });
  
  int start = 0;
  int end = 1e16;
  
  int dist = 0;
  
  while(start != end) {
    
    boost::disjoint_sets_with_storage<> uf(n);
    
    dist = (start + end) / 2;
  
    for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
      auto s1 = e->first->vertex((e->second + 1) % 3);
      auto s2 = e->first->vertex((e->second + 2) % 3);
      if(CGAL::squared_distance(s1->point(),s2->point()) <= dist) {
        uf.link(s1->info(),s2->info());
      } 
    }
    
    vector<int> values = vector<int>(n,0);
    for(auto bone : bones) {
      Point p = t.nearest_vertex(bone.first)->point();
      int idx = t.nearest_vertex(bone.first)->info();
      if(CGAL::squared_distance(p,bone.first) <= dist / 4) {
        values[uf.find_set(idx)]++;
      } 
    }
    
    if(*max_element(values.begin(),values.end()) < k) {
      start = dist+1;
    } else {
      end = dist;
    }
    
  }
  
  cout << std::fixed << *max_element(values.begin(),values.end()) << " " << max(dist,start) << "\n";
}

signed main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
