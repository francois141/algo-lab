#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef CGAL::Point_2<K> Point_2;
typedef Triangulation::Finite_faces_iterator Face_iterator;

using namespace std;

void solve(int n) {
  
  vector<Point_2> points;
  points.reserve(n);
  for(int i = 0; i < n;i++) {
    int x,y;
    cin >> x >> y;
    points.push_back(Point_2(x,y));
  }
  
  Triangulation t;
  t.insert(points.begin(),points.end());
  
  int m; cin >> m;

  for(int i = 0; i < m;i++) {
    int x,y;
    cin >> x >> y;
    Point_2 new_restaurant(x,y);
    Point_2 nearest_restaurant = t.nearest_vertex(new_restaurant)->point();
    
    cout << long(squared_distance(new_restaurant,nearest_restaurant)) << "\n";
  }
  
  return;
}

signed main() {
  
  int n;
  cin >> n;
  while(n != 0) {
    solve(n);
    cin >> n;
  } 
  
  return 0;
}
