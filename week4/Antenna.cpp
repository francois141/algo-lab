#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

#define int long

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Point_2<K> Point;
typedef CGAL::Min_circle_2_traits_2<K>  Traits;
typedef CGAL::Min_circle_2<Traits>      Min_circle;

double ceil_to_double(const K::FT& x) {
  double a = ceil(CGAL::to_double(x));
  while(a < x) a += 1; 
  while(a-1 >= x) a -= 1;
  return a;
}

void solve(int n) {
  vector<Point> points(n);
  
  for(int i = 0; i < n;i++) {
    int x,y;
    cin >> x >> y;
    points[i] = Point(x,y);
  }
  
  Min_circle mc(points.begin(), points.end(), true);
  Traits::Circle c = mc.circle();
  cout << fixed << setprecision(0);
  std::cout << ceil_to_double(sqrt(c.squared_radius())) << "\n";
}

signed main() {
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
