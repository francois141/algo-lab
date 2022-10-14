#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Segment_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Ray_2<K> Ray;
typedef CGAL::Point_2<K> Point;
typedef CGAL::Segment_2<K> Segment;

using namespace std;

void solve(int n) {
  
  long int a,b,x,y;
  cin >> a >> b >> x >> y;
  Ray ray = Ray(Point(a,b),Point(x,y));
  
  vector<Segment> segments(0);
  for(int i = 0; i < n;i++) {
    long int a,b,c,d;
    cin >> a >> b >> c >> d;
    segments.push_back(Segment(Point(a,b),Point(c,d)));
  }
  
  for(Segment seg : segments) {
    if(CGAL::do_intersect(ray,seg)) {
      cout << "yes\n";
      return;
    }
  }
  
  cout << "no\n";
}

int main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int n;
  cin >> n;
  
  while(n != 0) {
    solve(n);
    cin >> n;
  }
  
}
