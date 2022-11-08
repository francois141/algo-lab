#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef struct stall {
  int x,k,l,m;
} stall;

const int h1 = 0;
const int h2 = 1;
const int h3 = 2;

bool possible(const vector<stall> &stalls, int a, int p) {
  
  Program lp(CGAL::SMALLER, true, 0, true, 1);
  
  for(int i = 0; i < stalls.size();i++) {
    lp.set_a(h1,i,-stalls[i].k - a*a);
    lp.set_a(h2,i,-stalls[i].l - p*p);
    lp.set_a(h3,i,-stalls[i].m - a*p);
    lp.set_b(i,-stalls[i].x);
  }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  return !s.is_infeasible();
}

void solve() {
  
  int n;
  cin >> n;
  
  vector<stall> stalls(n);

  for(int i = 0; i < n;i++) {
    int f,c,k,l,m;
    cin >> f >> c >> k >> l >> m;
    stalls[i] = {f-c,k,l,m};
  }
  
  vector<int> a(25);
  vector<int> p(25);
  
  for(int i = 1; i <= 24;i++)
    cin >> a[i];
    
  for(int i = 1; i <= 24;i++)
    cin >> p[i];
    
  partial_sum(a.begin(), a.end(), a.begin());
  partial_sum(p.begin(), p.end(), p.begin());
  
  int best_score = INT_MAX;
  
  int left = 0;
  int right = 48;
  int bound = 24;
  
  vector<int> cache(25,-1);

  while(left <= right) {
    
    int hours = (left + right + 1) / 2;
    bool can = false; 
    
    for(int ai = max(0, hours - bound); ai <= min(hours,bound); ai++) {
      const int pi = hours - ai;
      
      if (cache[ai] > pi)
          continue;
      
      if(possible(stalls,a[ai],p[pi])) {
        can = true;
        break;
      }
      else {
        cache[ai] = max(cache[ai], pi);
      }
    }
    if(can) {
      best_score = hours;
      right = hours-1;
    }
    else {
      left = hours+1;
    }
  }

  if(best_score == INT_MAX) {
    cout << "Impossible!" << "\n";
  }
  else {
    cout << best_score << "\n";
  }
  
  return;
}

signed main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
  
}
