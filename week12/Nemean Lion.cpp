#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef CGAL::Point_2<K> Point;
typedef CGAL::Circle_2<K> Circle;
typedef K::FT Float;

typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef Triangulation::Finite_edges_iterator Edge_iterator;
typedef Triangulation::Finite_vertices_iterator Vertex_iterator;

typedef Triangulation::Edge Edge;

#define int long

using namespace std;

void solve() {
  Float s;
  int n,h;
  cin >> n >> s >> h;
  
  vector<Point> points(n);
  for(int i = 0; i < n;i++) {
    int x,y;
    cin >> x >> y;
    points[i] = Point(x,y);
  }
  
  Triangulation t;
  t.insert(points.begin(),points.end());
  
  int ans1 = 0;
  Float best_distance1 = LONG_MAX;
  int count1 = 0;
  
  for(Edge_iterator it = t.finite_edges_begin(); it != t.finite_edges_end(); ++it) {
    if(best_distance1 > t.segment(*it).squared_length()) {
      best_distance1 = t.segment(*it).squared_length();
      count1 = 1;
    } 
    else if(best_distance1 == t.segment(*it).squared_length()) {
      count1++;
    }
    ans1 = max(ans1,count1);
  }
  
  int ans2 = 0;
  Float best_distance2 = LONG_MAX;
  int count2 = 0;
  
  for(Face_iterator it = t.finite_faces_begin(); it != t.finite_faces_end(); ++it) {
    
    Point p1 = it->vertex(0)->point();
    Point p2 = t.dual(it);
    Float dist = CGAL::squared_radius(p1,p2);
  
    if(dist < best_distance2) {
      best_distance2 = dist;
      count2 = 1;
    } 
    else if(best_distance2 == dist) {
      count2++;
    }    
    
    ans2 = max(ans2,count2);
  }
  
  cout << ans1 << " " << ans2 << " " << h << " " << h << "\n";
}

signed main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
  
}