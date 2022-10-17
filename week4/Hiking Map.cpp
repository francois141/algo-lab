#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Triangle_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Line_2 Line;
typedef K::Triangle_2 Triangle;

using namespace std;

Point read_point() {
  int a,b;
  cin >> a >> b;
  return Point(a,b);
}

Line read_line() {
  int a,b; cin >> a >> b;
  int c,d; cin >> c >> d;
  return Line(Point(a,b),Point(c,d));
}

Triangle read_triangle() {

  Line l1 = read_line();
  Line l2 = read_line();
  Line l3 = read_line();
  
  auto o1 = CGAL::intersection(l1,l2);
  auto o2 = CGAL::intersection(l1,l3);
  auto o3 = CGAL::intersection(l2,l3);

  const Point *t1 = boost::get<Point>(&*o1);
  const Point *t2 = boost::get<Point>(&*o2);
  const Point *t3 = boost::get<Point>(&*o3);
  
  return Triangle(*t1,*t2,*t3);
}

void solve() {
  
  int n,m;
  cin >> m >> n;
  
  vector<Point> points;
  points.reserve(m);

  for(int i = 0; i < m; i++) {
    points.push_back(read_point());
  }
  
  vector<vector<bool>> covers(n,vector<bool>(m-1,false));
  Triangle triangle;
  for(int i = 0; i < n; i++) {
    triangle = read_triangle();
    vector<bool> inside(m);
    for(int j = 0; j < m;j++) {
      inside[j] = CGAL::do_intersect(triangle,points[j]);
    }
    for(int j = 0; j < m-1;j++) {
      if(inside[j] && inside[j+1]) {
        covers[i][j] = true;
      }
    }
  }
  
  const int length = m-1;
  vector<int> mask(length,0);
  
  int count = 0;
  int answer = INT_MAX;
  
  int left = 0;
  int right = 0;
  
  for(; left < n; left++) {
    for(int k = 0; k < length;k++) {
      if(covers[left][k]) {
        if(mask[k] == 0) 
          count++;
        mask[k]++;
      }
    }
    if(count < length)
      continue;
    while(right < left) {
      bool can = true;
      for(int k = 0; k < length;k++) {
        if(mask[k] <= 1 && covers[right][k]) {
          can = false;
          break;
        }
      }
      if(!can) 
        break;
      for(int k = 0; k < length;k++) {
        if(covers[right][k]) 
          mask[k]--;
      }
      right++;
    }
    answer = min(answer, left - right + 1);
  }
  
  cout << answer << "\n";
}

int main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int c;
  cin >> c;
  
  while(c--) 
    solve();
  
}
