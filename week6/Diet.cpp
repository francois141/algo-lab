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
  
  int n,m;
  cin >> n >> m;
  
  while(n != 0) {
  
    vector<pair<int,int>> nutriments(n);
    for(int i = 0; i < n;i++) {
      int nut_min,nut_max;
      cin >> nut_min >> nut_max;
      nutriments[i] = make_pair(nut_min,nut_max);
    }
    
    vector<int> prices(m);
    vector<vector<int>> values(m,vector<int>(n));
    for(int j = 0;j < m;j++) {
      cin >> prices[j];
      for(int i = 0; i < n;i++) {
        cin >> values[j][i];
      }
    }
    
    Program lp(CGAL::SMALLER, true, 0, false, 0);
    
    for(int i = 0; i < n;i++) {
      for(int j = 0; j < m;j++) {
        lp.set_a(j,2*i,values[j][i]);
        lp.set_a(j,2*i+1,-values[j][i]);
      }
      lp.set_b(2*i,nutriments[i].second);
      lp.set_b(2*i+1,-nutriments[i].first);
    }
    
    for(int j = 0; j < m;j++) {
      lp.set_c(j,prices[j]);
    }
    
    Solution s = CGAL::solve_linear_program(lp,ET());
    
    if(s.is_infeasible()) {
      cout << "No such diet." << "\n";
    }
    else {
      cout << floor(CGAL::to_double(s.objective_value())) << endl;      
    }

    cin >> n >> m;
  }
  
}
