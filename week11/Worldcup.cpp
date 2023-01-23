#include <bits/stdc++.h>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

#define int long

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef CGAL::Point_2<K> Point;

using namespace std;

int floor_to_long(const CGAL::Quotient<CGAL::Gmpz>& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

struct Warehouse {
  Point p;
  int supply;
  int alcohol;
};

struct Stadium {
  Point p;
  int demand;
  int upper;
};

void solve() {
  int n,m,c;
  cin >> n >> m >> c;
  
  vector<Point> points(0);
  
  vector<Warehouse> warehouses(n);
  for(int i = 0; i < n;i++) {
    int x,y,s,a;
    cin >> x >> y >> s >> a;
    warehouses[i] = {Point(x,y),s,a};
    points.push_back(Point(x,y));
  }
  
  vector<Stadium> stadiums(m);
  for(int j = 0; j < m;j++) {
    int x,y,d,u;
    cin >> x >> y >> d >> u;
    stadiums[j] = {Point(x,y),d,100*u}; 
    points.push_back(Point(x,y));
  }
  
  vector<vector<int>> revenues(n,vector<int>(m));
  for(int i = 0; i < n;i++) {
    for(int j = 0; j < m;j++) {
      cin >> revenues[i][j];
    }
  }
  
  Triangulation t;
  t.insert(points.begin(),points.end());
  
  vector<pair<Point,int>> contours(0);
  for(int k = 0; k < c;k++) {
    int x,y,r;
    cin >> x >> y >> r;
    Point p = Point(x,y);
    Point p2 = t.nearest_vertex(p)->point();
    if(CGAL::squared_distance(p,p2) < r*r) {
      contours.push_back(make_pair(Point(x,y),r*r));
    }
  }
  
  Program lp (CGAL::SMALLER, true, 0, false, 0);
  int equation = 0;
  
  // bind supply
  for(int i = 0; i < n;i++) {
    for(int j = 0; j < m;j++) lp.set_a(i*m + j,equation,1);
    lp.set_b(equation,warehouses[i].supply);
    equation++;
  }
  
  // bind quantity and alcohol
  for(int j = 0; j < m;j++) {
    
    for(int i = 0; i < n;i++) lp.set_a(i*m + j, equation, 1);
    lp.set_b(equation, stadiums[j].demand);
    equation++;
    
    for(int i = 0; i < n;i++) lp.set_a(i*m + j, equation, -1);
    lp.set_b(equation, -stadiums[j].demand);
    equation++;
    
    for(int i = 0; i < n;i++) lp.set_a(i*m + j, equation, warehouses[i].alcohol);
    lp.set_b(equation, stadiums[j].upper);
    equation++;
  }
  
  for(int i = 0; i < n;i++) {
    for(int j = 0; j < m;j++) {
      int rev = 100*revenues[i][j];
      for(auto c: contours) {
        auto dist1 = CGAL::squared_distance(warehouses[i].p,c.first);
        auto dist2 = CGAL::squared_distance(stadiums[j].p, c.first);
        if(dist1 < c.second && dist2 > c.second) rev--;
        if(dist1 > c.second && dist2 < c.second) rev--;
      }
      lp.set_c(i*m+j, -rev);
    }
  }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  
  if(s.is_infeasible()) {
    cout << "RIOT!" << "\n";
    return;
  }
  
  cout << floor_to_long(-s.objective_value() / 100) << "\n";
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
