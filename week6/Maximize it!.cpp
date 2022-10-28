#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

const int X = 0;
const int Y = 1;
const int Z = 2;

int main() {
  
  while (true) {
    int p,a,b;
    cin >> p >> a >> b;
    
    if(p == 0) {
      return 0;
    }
    if(p == 1) {
      Program lp(CGAL::SMALLER, true, 0, false, 0); 
      
      lp.set_a(X,0,1); lp.set_a(Y,0,1); lp.set_b(0,4);
      lp.set_a(X,1,4); lp.set_a(Y,1,2); lp.set_b(1,a*b);
      lp.set_a(X,2,-1); lp.set_a(Y,2,1); lp.set_b (2,1);

      lp.set_c(X,a); lp.set_c(Y,-b);
      
      Solution s = CGAL::solve_linear_program(lp,ET());
      
      if(s.is_infeasible()) {
        cout << "no" << "\n";
      } else if(s.is_unbounded()) {
        cout << "unbounded" << "\n";
      } else {
        cout << floor(CGAL::to_double(-s.objective_value())) << endl;
      }
    }
    if(p == 2) {
      Program lp(CGAL::SMALLER, false, 0, true, 0); 

      
      lp.set_a(X,0,-1); lp.set_a(Y,0,-1); lp.set_a(Z,0,0);lp.set_b(0,4);
      lp.set_a(X,1,-4); lp.set_a(Y,1,-2); lp.set_a(Z,1,-1);lp.set_b(1,a*b);
      lp.set_a(X,2,1); lp.set_a(Y,2,-1); lp.set_a(Z,2,0);lp.set_b(2,1);

      lp.set_c(X,a); lp.set_c(Y,b); lp.set_c(Z,1); 
      
      Solution s = CGAL::solve_linear_program(lp,ET());
      
      if(s.is_infeasible()) {
        cout << "no" << "\n";
      } else if(s.is_unbounded()) {
        cout << "unbounded" << "\n";
      } else {
        cout << ceil(CGAL::to_double(s.objective_value())) << endl;
      }
      
    }
  }

  return 0;
}
