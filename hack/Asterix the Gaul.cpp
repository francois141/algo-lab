#include <bits/stdc++.h>

#define int long

using namespace std;

struct Move {
  int d;
  int t;
};

int n,m,D,T;
vector<Move> movement;
vector<int> bonus;

void generate(vector<Move>&set, int from, int to, int b, Move mv) {
  if(mv.t > T) return;
  if(from == to) {
    set.push_back(mv);
    return;
  }
  
  Move new_move = Move{mv.d+movement[from].d+b,mv.t+movement[from].t};
  
  generate(set,from+1,to,b,new_move);
  generate(set,from+1,to,b,mv);
}

bool compute(int b) {
  
  vector<Move> subset1(0);
  vector<Move> subset2(0);
  
  generate(subset1,0,n/2,b,Move{0,0});
  generate(subset2,n/2,n,b,Move{0,0});
  
  auto comp = [](Move m1, Move m2){
    return m1.t < m2.t;
  };
  
  sort(subset1.begin(),subset1.end(),comp);
  sort(subset2.begin(),subset2.end(),comp);
  
  for(int i = 1; i < subset1.size();i++) subset1[i].d = max(subset1[i].d,subset1[i-1].d);
  for(int i = 1; i < subset2.size();i++) subset2[i].d = max(subset2[i].d,subset2[i-1].d);
  
  for(auto move : subset1) {
    auto move2 = lower_bound(subset2.begin(), subset2.end(), T - move.t,[&](const Move &move, int value){
      return move.t < value;
    }) - 1;
    
    if(move.d + move2->d >= D)
      return true;
  }  

  return false;
}

void solve() {
  cin >> n >> m >> D >> T;
  
  movement = vector<Move>(n);
  for(int i = 0; i < n;i++) cin >> movement[i].d >> movement[i].t;
  
  bonus = vector<int>(m+2);
  for(int i = 1; i <= m;i++) cin >> bonus[i];
  bonus.back() = 0;
  
  // Binary search over the solution space
  int start = 0;
  int end = m+2;
  while(start != end) {
    int middle = (start + end) / 2;
    if(compute(bonus[middle])) {
      end = middle;
    } else {
      start = middle+1;
    }
  }
  
  if(start == m+2) {
    cout << "Panoramix captured" << "\n";
  } else {
    cout << start << "\n";
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
