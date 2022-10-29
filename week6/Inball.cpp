#include <iostream>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

int main() {
  
  int n,d,a,b;
  cin >> n;
  
  while(n != 0) {
    
    cin >> d;
    
    Program lp = Program(CGAL::SMALLER, false, 0, false, 0);
    
    for(int i = 0; i < n;i++) {
      int norm = 0;
      for(int j = 0;j < d;j++) {
        cin >> a;
        norm += a * a;
        lp.set_a(j,i,a);
      }
      lp.set_a(d,i,sqrt(norm));
      cin >> b;
      lp.set_b(i,b);
    }
    
    lp.set_l(d,true,0);
    lp.set_c(d,-1);
      
    Solution s = CGAL::solve_linear_program(lp, ET());
      
    if(s.is_infeasible()) {
      cout << "none" << "\n";
    } else if(s.is_unbounded()) {
      cout << "inf" << "\n";
    } else {
      cout << -s.objective_value_numerator() / s.objective_value_denominator() << "\n";
    }
  
    cin >> n;
  }
  
  return 0;
}
