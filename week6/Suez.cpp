#include <iostream>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

#define int long 

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef CGAL::Quotient<int> Fraction;

using namespace std;

void solve() {
  
  int n,m,h,w;
  cin >> n >> m >> h >> w;
  
  vector<pair<int,int>> positions(n);
  vector<pair<int,int>> hanging(m);
  
  for(int i = 0; i < n;i++) {
    int x,y;
    cin >> x >> y;
    positions[i] = make_pair(x,y);
  }
  
  for(int j = 0; j < m;j++) {
    int x,y;
    cin >> x >> y;
    hanging[j] = make_pair(x,y);
  }
  
  Program lp = Program(CGAL::SMALLER, true, 1, false, 0);
  int equation = 0;
  
  for(int i = 0; i < n;i++) {
    Fraction fraction(1,0);
    for(int j = 0; j < m;j++) {
      int cx = 2*abs(positions[i].first - hanging[j].first) - w;
      int cy = 2*abs(positions[i].second - hanging[j].second) - h;
      Fraction other;
      if(cx*h >= cy*w) other = {cx,w};
      else other = {cy,h};
      if(fraction.denominator() == 0 || other < fraction)
        fraction = other;
    }
    lp.set_a(i,equation,fraction.denominator());
    lp.set_b(equation,fraction.numerator());
    equation++;
  }
  
  for(int i = 0; i < n;i++) {
    Fraction fraction(1,0);
    for(int j = i+1; j < n;j++) {
      int cx = 2*abs(positions[i].first - positions[j].first);
      int cy = 2*abs(positions[i].second - positions[j].second);
      if(cx*h >= cy*w) {
        lp.set_a(i,equation,w);
        lp.set_a(j,equation,w);
        lp.set_b(equation,cx);
      }
      else {
        lp.set_a(i,equation,h);
        lp.set_a(j,equation,h);
        lp.set_b(equation,cy);
      }
      equation++;
    }
  }
  
  for(int i = 0; i < n;i++) {
    lp.set_c(i, -2*(h + w));
  }
  
  Solution s = CGAL::solve_linear_program(lp,ET());
  
  int numerator = abs(s.objective_value().numerator().to_double());
  int denominator = abs(s.objective_value().denominator().to_double());
  
  int solution = numerator / denominator;
  int rest = numerator % denominator;
  if(rest > 0) solution++;
  
  cout << solution << "\n";
  
  return;
}

signed main() {
  
  int t;
  cin >> t;
  
  while(t--)
    solve();

  return 0;  
}
