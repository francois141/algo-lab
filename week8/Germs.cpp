#include <iostream>
#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Point_2<K> Point;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Vertex_iterator Vertex_iterator;

using namespace std;

// Given the distance ==> Say how long it takes before it collides
double transform(double distance) {
  return sqrt((sqrt(distance) - 1) / 2);
}

void solve(int n) {
  
  int left, bottom, right, top;
  cin >> left >> bottom >> right >> top;
  
  vector<Point> points(n);
  for(int i = 0; i < n;i++) {
    int x,y;
    cin >> x >> y;
    points[i] = Point(x,y);
  }
  
  Triangulation t;
  t.insert(points.begin(),points.end());
  
  vector<double> distances;
  distances.reserve(n);
  
  for(Vertex_iterator vertex_it = t.finite_vertices_begin(); vertex_it != t.finite_vertices_end(); ++vertex_it) {
    
    double x = vertex_it->point().x();
    double y = vertex_it->point().y();
    
    double min_distance = sqrt(std::min({abs(left - x),abs(right - x),abs(bottom - y),abs(top - y)}) - 0.5);
    
    auto c = t.incident_edges(vertex_it);
    if(c != 0) {
      do {
        if(t.is_infinite(c)) continue;
        min_distance = min(min_distance,transform(t.segment(c).squared_length()));
      } while(++c != t.incident_edges(vertex_it)); 
    }

    distances.push_back(min_distance);
  }
  
  sort(distances.begin(),distances.end());
  
  cout << ceil(distances[0]) << " " << ceil(distances[n/2]) << " " << ceil(distances.back()) << "\n";
  
  return;
}

int main() {
  
  int n;
  cin >> n;
  
  while(n != 0) {
    solve(n); 
    cin >> n;
  }
  
  return 0;
}
