#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<size_t,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;

typedef CGAL::Point_2<K> Point;

using namespace std;

void solve(int n) {
  
  vector<Point> points(n);
  for(int i = 0; i < n;i++) {
    int x,y;
    cin >> x >> y;
    points[i] = Point(x,y);
  }
  
  Triangulation t;
  t.insert(points.begin(),points.end());
  
  unsigned int nb_faces = 1;
  for(auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f) {
    f->info() = nb_faces++;
  }
  
  vector<vector<pair<int,double>>> edges(nb_faces);
  for(auto f = t.finite_faces_begin(); f != t.finite_faces_end();++ f) {
    int u = f->info();
    
    for(int i = 0; i < 3;i++) {
      auto f2 = f->neighbor(i);
      int v = t.is_infinite(f2) ? 0 : f2->info();
      
      auto p1 = f->vertex((i + 1) % 3)->point();
      auto p2 = f->vertex((i + 2) % 3)->point();
      
      double dist = CGAL::squared_distance(p1,p2);
      edges[u].push_back({v, dist});
      if(v == 0) {
        edges[v].push_back({u, dist});
      }
    }
  }
  
  vector<double> bottleneck(nb_faces, -1);
  
  priority_queue<pair<double,int>> Q;
  Q.push({std::numeric_limits<double>::max(), 0});
  
  while(!Q.empty()) {
  
    auto p = Q.top(); Q.pop();
    
    double val = p.first;
    int u = p.second;
    
    if(bottleneck[u] != -1) {
      continue;
    }
    
    bottleneck[u] = val;
      
    for(auto next : edges[u]) {
      double dist = next.second;
      int v = next.first;
      if(bottleneck[v] == -1) Q.push({min(dist,val),v});
    }
    
  }
  
  int m;
  cin >> m;
  
  for(int i = 0; i < m;i++) {
    int x,y;
    double d;
    cin >> x >> y >> d;
    auto p = Point(x,y);
    double dist = CGAL::squared_distance(p, t.nearest_vertex(p)->point());
    
    if(d > dist) {
      cout << "n";
      continue;
    }
    
    auto f = t.locate(p);
    auto idx = t.is_infinite(f) ? 0 : f->info();
    
    if(4*d > bottleneck[idx]) {
      cout << "n";
    }
    else {
      cout << "y";
    }
    
  }
  cout << "\n";
  return;
}

int main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int n;
  cin >> n;
  
  while(n != 0) {
    solve(n);
    cin >> n;
  }
  
  return 0;
}
