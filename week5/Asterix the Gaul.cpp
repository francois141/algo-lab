#include <bits/stdc++.h>

#define int long

using namespace std;

struct Move {
  int d;
  int t;
  bool operator<(const Move &other) const {
    return this->t < other.t;
  }
};

int n,m,D,T;
vector<Move> moves;

void generate(vector<Move> &curr, int from, int to, int boost, Move move) {
  if(move.t >= T) return;
  if(from == to) {
    curr.push_back(move);
    return;
  }
  
  generate(curr,from+1,to,boost,move);
  generate(curr,from+1,to,boost,{move.d + moves[from].d + boost, move.t + moves[from].t});
}

bool compute(int boost) {
  vector<Move> moves1(0); generate(moves1, 0,n/2,boost,Move{0,0}); 
  vector<Move> moves2(0); generate(moves2, n/2,n,boost,Move{0,0});

  sort(moves1.begin(),moves1.end());
  sort(moves2.begin(),moves2.end());
  
  for(int i = 1; i < moves1.size(); i++) moves1[i].d = max(moves1[i].d,moves1[i-1].d); 
  for(int i = 1; i < moves2.size(); i++) moves2[i].d = max(moves2[i].d,moves2[i-1].d); 
  
  for(auto mv1 : moves1) {
    auto mv2 = lower_bound(moves2.begin(),moves2.end(),T - mv1.t,[](Move m,int t){
      return m.t < t;
    }) - 1;
    if(mv2->d + mv1.d >= D) 
      return true;
  }
  
  return false;
}

void solve() {

  cin >> n >> m >> D >> T;
  
  moves = vector<Move>(n);
  for(int i = 0; i < n;i++) {
    int d,t;
    cin >> d >> t;
    moves[i] = {d,t};
  }
  
  vector<int> boost(m+2,0);
  for(int i = 1; i <= m;i++) {
    cin >> boost[i];
  }
  
  int start = 0;
  int end = m+1;
  
  while(start != end) {
    int middle = (start + end) / 2;
    if(compute(boost[middle])) {
      end = middle;
    } else {
      start = middle + 1;
    }
  } 
  
  if(start == m+1) {
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
