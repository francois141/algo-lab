#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Circle_trait;
typedef CGAL::Min_circle_2<Circle_trait> Min_circle;
typedef K::Point_2 P;

void ceil_to_cout(const K::FT& x) {
  double a = ceil(CGAL::to_double(x));
  while(a < x) a += 1; 
  while(a-1>= x) a -= 1;
  cout  << fixed << setprecision(0) << a << "\n";
}

void solve(int n) {

  vector<P> points;
  
  for(int i = 0; i < n;i++) {
    long int x,y;
    cin >> x >> y;
    points.push_back(P(x,y));
  }
  
  Min_circle min_circle(points.begin(),points.end(),true);
  Circle_trait::Circle circle = min_circle.circle();
  
  ceil_to_cout(sqrt(circle.squared_radius()));
  
  return;
}


int main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int n;
  cin >> n;
  
  while(n != 0) {
    solve(n);
    cin >> t;
  }

  return 0;
}
