#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#define int long long

using namespace std;

typedef struct Move {
  int dist;
  int time;
  bool operator <(const Move &other) const {
    return time < other.time;
  }
} Move;

vector<Move> moves;
int n,m,D,T;

void getMoves(vector<Move>& move,int i,int end,int boost,int distance,int timeLeft) {
  
  if(timeLeft <= 0)
    return;
    
  if(i == end) {
    if(distance >= 0) {
      move.push_back({distance,T - timeLeft});
    }
    return; 
  }
  
  getMoves(move,i+1,end,boost,distance + moves[i].dist + boost,timeLeft - moves[i].time);
  getMoves(move,i+1,end,boost,distance,timeLeft);
}

bool reach(int boost) {

  vector<Move> p1;
  vector<Move> p2; 
  
  getMoves(p1,0,n/2,boost,0,T);
  getMoves(p2,n/2,n,boost,0,T);
  
  sort(p1.begin(),p1.end());
  sort(p2.begin(),p2.end());
  
  for(int i = 1; i < p1.size();i++) {
    p1[i].dist = max(p1[i].dist,p1[i-1].dist);
  }
  
  for(int i = 1; i < p2.size();i++) {
    p2[i].dist = max(p2[i].dist,p2[i-1].dist);
  }
  
  for(auto move : p1) {
    auto move2 = lower_bound(p2.begin(), p2.end(), T - move.time,[&](const Move &move, int value){
      return move.time < value;
    }) - 1;
    
    if(move.dist + move2->dist >= D)
      return true;
  }  
  
  return false;
}

void solve() {
  
  cin >> n >> m >> D >> T;
  
  moves = vector<Move>(0);
  for(int i = 0; i < n;i++) {
    int d,t;
    cin >> d >> t;
    moves.push_back({d,t});
  }
  
  vector<int> s(m+2);
  s[0] = 0;
  for(int i = 1; i <= m;i++) {
    cin >> s[i];
  }
  
  // Binary search over the solution space
  int start = 0;
  int end = m+1;
  
  while(start != end) {
    int middle = (start + end) / 2;
    
    if(reach(s[middle])) {
      end = middle;
    } else {
      start = middle+1;
    }
  }
  if(start == m+1) 
    cout << "Panoramix captured" << "\n";
  else
    cout << start << "\n"; 
    
  return;
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
