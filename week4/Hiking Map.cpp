#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Point_2<K> Point;
typedef CGAL::Line_2<K> Line;
typedef CGAL::Triangle_2<K> Triangle;

using namespace std;

inline Point read_point() {
  int x,y; cin >> x >> y;
  return Point(x,y);
}

inline bool check(const vector<Point> &points, const Point &point) {
  return !CGAL::right_turn(points[0],points[1],point) && !CGAL::right_turn(points[2],points[3],point) && !CGAL::right_turn(points[4],points[5],point);
}

void solve() {
  int n,m;
  cin >> m >> n;
  
  vector<Point> points = vector<Point>(m);
  for(int i = 0; i < m;i++) {
    points[i] = read_point();
  }
  
  vector<vector<Point>> triangles = vector<vector<Point>>(n,vector<Point>(0));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < 6; j++) {
      int x,y;
      cin >> x >> y;
      triangles[i].push_back(Point(x,y));
    }
    for(int j = 0; j < 6;j+=2) {
      if(CGAL::right_turn(triangles[i][j],triangles[i][j+1],triangles[i][(j+2) % 6])) std::swap(triangles[i][j],triangles[i][j+1]); 
    }
  }
  
  vector<vector<bool>> contains(n,vector<bool>(m-1,false));
  
  for(int i = 0; i < n;i++) {
    vector<bool> inside(m,false);
    for(int j = 0; j < m;j++) {
      if(check(triangles[i],points[j]))
        inside[j] = true;
    }
    for(int j = 0; j < m-1;j++) {
      if(inside[j] && inside[j+1]) contains[i][j] = true;
    }
  }
  
  int best = INT_MAX;
  int start = -1;
  int end = 0;
  
  int counter = 0;
  vector<int> mask(m-1,0);
  
  while(start != n-1) {
    start++;
    for(int j = 0; j < m-1;j++) {
      if(contains[start][j]) {
        if(mask[j] == 0) counter++;
        mask[j]++;
      }
    }
    
    while(counter == m-1) {
      best = min(best,start-end+1);
      for(int j = 0; j < m-1;j++) {
        if(contains[end][j]) {
          mask[j]--;
          if(mask[j] == 0) counter--; 
        }
      }
      end++;
    }
  }
  
  cout << best << "\n";
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
