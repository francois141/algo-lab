#include <bits/stdc++.h>

#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Gmpz.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

#define int long

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef CGAL::Point_2<K> Point;

typedef CGAL::Gmpq IT;
typedef CGAL::Gmpq ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

struct Positions {
  Point p;
  double max_dist;
};

struct Asteroid {
  Point p;
  int d;
};

void solve() {
  int a,s,b;
  long e;
  cin >> a >> s >> b;
  cin >> e;
  
  vector<Asteroid> asteroids = vector<Asteroid>(a);
  vector<Positions> positions = vector<Positions>(s);
  vector<Point> hunters = vector<Point>(b);
  
  for(int i = 0; i < a; i++) {
    int x,y,d;
    cin >> x >> y >> d;
    asteroids[i] = Asteroid{Point(x,y),d};
  }
  
  for(int i = 0; i < s; i++) {
    int x,y;
    cin >> x >> y;
    positions[i] = {Point(x,y),DBL_MAX};
  }
  
  for(int i = 0; i < b; i++) {
    int x,y;
    cin >> x >> y;
    hunters[i] = Point(x,y);
  }
  
  Triangulation t;
  t.insert(hunters.begin(), hunters.end());
  
  if(b > 0) {
    for(int i = 0; i < s;i++) {
      Point tmp = t.nearest_vertex(positions[i].p)->point();
      positions[i].max_dist = squared_distance(tmp,positions[i].p);
    }
  }

  Program lp(CGAL::SMALLER, true, 0, false);
  
  for(int i = 0; i < a;i++) {
    for(int j = 0; j < s;j++) {
      if(positions[j].max_dist >= CGAL::squared_distance(positions[j].p, asteroids[i].p)) {
        lp.set_a(j,i,-CGAL::Gmpq(1, max(K::FT(1), CGAL::squared_distance(positions[j].p, asteroids[i].p))));
      }
    }
    lp.set_b(i,-asteroids[i].d);
  }
  
  for(int j = 0; j < s;j++) {
    lp.set_a(j,a,1);
  }
  lp.set_b(a,e);
  
  Solution solution = CGAL::solve_linear_program(lp, ET());
  if (solution.is_infeasible()) {
    cout << "n" << "\n";
  } else {
    cout << "y" << "\n";
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
