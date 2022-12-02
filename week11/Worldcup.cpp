#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

#define int long

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef CGAL::Point_2<K> Point;

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

long floor_to_long(const CGAL::Quotient<CGAL::Gmpz>& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

struct Warehouse {
  Point pos;
  int supply;
  int alcohol;
};

struct Stadium {
  Point pos;
  int demand;
  int maxAlcohol;
};

void solve() {
  
  int n,m,c;
  cin >> n >> m >> c;
  
  vector<Point> points = vector<Point>(n+m); 
  vector<Warehouse> warehouses = vector<Warehouse>(n);
  vector<Stadium> stadiums = vector<Stadium>(m);
  vector<vector<int>> revenues = vector<vector<int>>(n,vector<int>(m));
  vector<pair<Point, int>> contours(0);
  
  for(int i = 0; i < n;i++) {
    int x,y,s,a;
    cin >> x >> y >> s >> a;
    warehouses[i] = {Point(x,y), s, a};
    points[i] = Point(x,y);
  }
  
  for(int i = 0; i < m;i++) {
    int x,y,d,u;
    cin >> x >> y >> d >> u;
    stadiums[i] = {Point(x,y), d, 100*u};
    points[n+i] = Point(x,y);
  }
  
  for(int i = 0; i < n;i++) {
    for(int j = 0; j < m;j++) {
      cin >> revenues[i][j];
    }
  }
  
  Triangulation t;
  t.insert(points.begin(),points.end());
  
  for(int i = 0; i < c;i++) {
    int x,y,r;
    cin >> x >> y >> r;
    Point p = Point(x,y);
    int distance = CGAL::squared_distance(p,t.nearest_vertex(p)->point());
    if(distance < r*r)
      contours.push_back({p,r*r});
  }
  
  Program lp(CGAL::SMALLER, true, 0, false, 0); 
  int counter = 0;
  
  // Set constraints for supply
  for(int i = 0; i < n;i++) {
    for(int j = 0; j < m;j++)
      lp.set_a(i*m + j,counter,1);
    lp.set_b(counter,warehouses[i].supply);
    counter++;
  }
   
  // Set constraints for alcohol & quantity
  for(int j = 0; j < m;j++) {
    for(int i = 0; i < n;i++) {
      lp.set_a(j + i*m,counter,warehouses[i].alcohol);
    }
    lp.set_b(counter,stadiums[j].maxAlcohol);
    counter++;
    
    for(int i = 0; i < n;i++) {
      lp.set_a(j + i*m,counter,1);
    }
    lp.set_b(counter,stadiums[j].demand);
    counter++;
    
    for(int i = 0; i < n;i++) {
      lp.set_a(j + i*m,counter,-1);
    }
    lp.set_b(counter,-stadiums[j].demand);
    counter++;
  }

  // Set objective function
  for(int i = 0; i < n;i++) {
    for(int j = 0; j < m;j++) {
      int revenue = 100*revenues[i][j];
      for(auto c: contours) {
        int distance1 = CGAL::squared_distance(warehouses[i].pos, c.first);
        int distance2 = CGAL::squared_distance(stadiums[j].pos, c.first);
        if(distance1 < c.second && distance2 > c.second) revenue -= 1;
        if(distance2 < c.second && distance1 > c.second) revenue -= 1;
      }
      lp.set_c(i*m+j, -revenue);
    }
  }
  
  // Get max revenue
  Solution s = CGAL::solve_linear_program(lp,ET());
  if(s.is_infeasible()) 
    cout << "RIOT!" << "\n";
  else 
    cout << floor_to_long(-s.objective_value() / 100) << endl;
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
