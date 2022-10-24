#include <iostream>
#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/enum.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Ray_2<K> Ray;
typedef CGAL::Point_2<K> Point;
typedef CGAL::Line_2<K> Line;

using namespace std;

typedef struct Biker {
  Ray r;
  Line l;
  int index;
  long int y0;
} Biker;


void solve() {
  
  int n;
  cin >> n;
  
  vector<Biker> motos(0);
  
  for(int i = 0; i < n;i++) {
    long y0,x1,y1;
    cin >> y0 >> x1 >> y1;
    Line l;
    if(y0 < y1) {
      l = Line(Point(0,y0),Point(x1,y1));
    }
    else {
      l = Line(Point(0,-y0),Point(x1,-y1));
    }
    Ray r = Ray(Point(0,y0),Point(x1,y1));
    motos.push_back({r,l,i,y0});
  }

  sort(motos.begin(),motos.end(),[](const Biker &b1, const Biker &b2) -> bool {
    return b1.y0 > b2.y0;
  });
  
  vector<bool> sol(n,true);
  
  for(int i = 1; i < n;i++) {
    
    for(int j = i-1; j >= 0;j--) {
      if(!sol[motos[j].index]) {
        continue;
      }
      if(!CGAL::do_intersect(motos[i].r,motos[j].r)){
        break;
      } 
      
      auto result = CGAL::compare_slope(motos[i].l, motos[j].l);
      if (result == CGAL::Comparison_result::LARGER) {
        sol[motos[i].index] = false;
        break; 
      }
      else {
        sol[motos[j].index] = false;
      }
    }
  }
  
  for(int i = 0; i < sol.size();i++) {
    if(sol[i])
      cout << i << " ";
  }
  cout << "\n";
  
  return;
}

signed main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
  
  return 0;
}
