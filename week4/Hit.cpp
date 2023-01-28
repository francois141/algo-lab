#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#define int long

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Point_2<K> Point;
typedef CGAL::Segment_2<K> Segment;
typedef CGAL::Ray_2<K> Ray;

void solve(int n) {
  int x,y,a,b;
  cin >> x >> y >> a >> b;
  
  Ray ray = Ray(Point(x,y),Point(a,b));
  
  vector<Segment> segments(n);
  for(int i = 0; i < n;i++) {
    int r,s,t,u;
    cin >> r >> s >> t >> u;
    segments[i] = Segment(Point(r,s),Point(t,u));
  }
  
  random_shuffle(segments.begin(),segments.end());
  
  bool hit = false;
  
  for(auto seg: segments) {
    if(CGAL::do_intersect(seg,ray)) {
      hit = true;
      break;
    }
  }
  
  cout << ((hit) ? "yes" : "no") << endl;
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
