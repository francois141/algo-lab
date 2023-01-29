#include <bits/stdc++.h>

#define int long

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VII;
typedef vector<VII> VIII;
typedef vector<VIII> VIIII;

VIIII dp;
VI f;
int n,k,m;

struct Q 
{
  int f1;
  int f2;
  int f3;
};

struct K
{
  int q1;
  int q2;
  int q3;
};

K encode(Q &north, Q &south, int diff) {
  int q1 = north.f1*5+north.f2;
  int q2 = south.f1*5+south.f2;
  return {q1,q2,diff+12};
};

Q insert(Q &q, int val) {
  return Q{val,q.f1,q.f2};
};

int size(Q &q) {
  if(m == 2) 
    return set<int>({0,q.f1,q.f2}).size() - 1;
  return set<int>({0,q.f1,q.f2,q.f3}).size() - 1;
};

int excitement(Q &q,int diff) {
  return size(q)*1000 - int(pow(2,abs(diff)));
}

int solve(int idx, Q north, Q south, int diff) {
  
  if(abs(diff) >= 12) return INT_MIN;
  if(idx < 0) return 0;
  
  K key = encode(north,south,diff);
  if(dp[idx][key.q1][key.q2][key.q3] != -1) return dp[idx][key.q1][key.q2][key.q3];
  
  Q new_north = insert(north,f[idx]);
  Q new_south = insert(south,f[idx]);
  
  int val_north = excitement(new_north, diff+1);
  int val_south = excitement(new_south, diff-1);
  
  int best = INT_MIN;
  if(val_north >= 0) 
  {
    best = max(best,val_north + solve(idx-1, new_north,south,diff+1));
  }
  if(val_south >= 0) 
  {
    best = max(best,val_south + solve(idx-1, north,new_south,diff-1));
  }
  
  return dp[idx][key.q1][key.q2][key.q3] = best;
}

void solve() {
  
  cin >> n >> k >> m;
  
  f = VI(n);
  for(int i = n-1; i >= 0;i--) {
    cin >> f[i];
    f[i]++;
  }
  
  dp = VIIII(n, VIII(25,VII(25,VI(25,-1))));
  
  Q init_empty = {0,0,0};
  cout << solve(n-1,init_empty,init_empty, 0) << endl;
}

int main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
  
  return 0;
}
