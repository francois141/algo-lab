#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

#define int long

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;

typedef CGAL::Point_2<K> Point;
typedef CGAL::Circle_2<K> Circle;

K::FT get_face_radius(Triangulation &t, Triangulation::Face_handle f) {
  if(t.is_infinite(f)) return K::FT(LONG_MAX);
  return Circle(f->vertex(0)->point(),f->vertex(1)->point(),f->vertex(2)->point()).squared_radius();
}

void solve() {
  int n,s,h;
  cin >> n >> s >> h;
  
  vector<pair<Point,int>> points(n);
  for(int i = 0; i < n;i++) {
    int x,y;
    cin >> x >> y;
    points[i] = make_pair(Point(x,y),i);
  } 
  
  Triangulation t;
  t.insert(points.begin(),points.end());
  
  int a_2 = 0;
  int a_3 = 0;
  int a_s = 0;
  int a_max = 0;
  
  vector<pair<K::FT,int>> events;
  
  auto min_squared_radius = K::FT(LONG_MAX);
  for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    auto v_left = e->first->vertex((e->second + 1) % 3);
    auto v_right = e->first->vertex((e->second + 2) % 3); 
    
    Point midpoint = CGAL::midpoint(v_left->point(), v_right->point());
    int v_nearest = t.nearest_vertex(midpoint)->info();
    
    auto f1 = e->first;
    auto f2 = t.mirror_edge(*e).first;
    auto f1_radius = get_face_radius(t,f1);
    auto f2_radius = get_face_radius(t,f2);
    
    K::FT min_radius;
    K::FT max_radius = max(f1_radius,f2_radius);
    if(v_nearest != v_left->info() && v_nearest != v_right->info()) {
      min_radius = min(f1_radius,f2_radius);
    } else {
      min_radius = t.segment(*e).squared_length() / 4;
    }
    
    if(K::FT(s) >= min_radius && K::FT(s) <= max_radius) {
      a_s++;
    }
    
    events.push_back(make_pair(min_radius,0));
    events.push_back(make_pair(max_radius,1));

    auto distance = t.segment(e).squared_length();
    if(distance < min_squared_radius) {
      a_2 = 1;
      min_squared_radius = distance;
    } else if(distance == min_squared_radius) {
      a_2++;
    }
  }
  
  auto min_squared_3 = K::FT(LONG_MAX);
  for(auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f) {
    auto radius = get_face_radius(t,f);
    if(radius < min_squared_3) {
      min_squared_3 = radius;
      a_3 = 1;
    } else if(radius == min_squared_3) {
      a_3++;
    }
  }
  
  sort(events.begin(),events.end());
  int curr = 0;
  
  for(auto e: events) {
    if(e.second == 0) curr++;
    else curr--;
    a_max = max(a_max,curr);
  } 
  
  cout << a_2 << " " << a_3 << " " << a_s << " " << a_max << "\n";
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;
  
  while(t--)
    solve();
}
