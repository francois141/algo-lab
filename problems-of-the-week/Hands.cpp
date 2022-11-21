#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

#include <boost/pending/disjoint_sets.hpp>

#define int long

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef CGAL::Point_2<K> Point;

using namespace std;

typedef struct Edge {
  int x;
  int y;
  int w;
} Edge;

int maxFamilies(vector<int> &c, int k) {
  
  int o = c[k];
  
  if(k == 4) {
    if(c[3] <= c[1]) {
      o += c[3];
      o += ((c[1]-c[3])/2+c[2]) / 2;
    }
    else{
      o += c[1];
      o += ((c[3]-c[1])+c[2]) / 2;
    }
  }
  
  else if(k == 3) {
    if(c[2] <= c[1]) {
      o += c[2];
      o += (c[1] - c[2]) / 3;
    }
    else {
      o += c[1];
      o += (c[2] - c[1]) / 2;
    }
  }
  
  else if(k == 2) {
    o += c[1] / 2;
  }
  
  return o;
}
void solve() {
  
  int n,k,f0,s0;
  cin >> n >> k >> f0 >> s0;
  
  vector<pair<Point,int>> points(n);
  for(int i = 0; i < n;i++) {
    int x,y;
    cin >> x >> y;
    points[i] = {Point(x,y),i};
  }
  
  Triangulation t;
  t.insert(points.begin(),points.end());
  
  vector<Edge> edges(0);
  for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    int p1 = e->first->vertex((e->second + 1) % 3)->info();
    int p2 = e->first->vertex((e->second + 2) % 3)->info();
    if(p1 > p2) swap(p1,p2);
    edges.push_back({p1,p2, long(t.segment(e).squared_length())});
  }
  
  sort(edges.begin(),edges.end(),[](const Edge &e1, const Edge &e2) -> bool {
    return e1.w < e2.w;
  });
  
  boost::disjoint_sets_with_storage<> uf(n);
  
  int n_components = n;
  
  vector<int> sizeComponent(n,1);
  vector<int> componentOfSize(k+1,0);
  componentOfSize[1] = n;
  
  int s_sol = 0;
  int f_sol = 0;
  
  for(auto e : edges) {
    // Get Index
    int c1 = uf.find_set(e.x);
    int c2 = uf.find_set(e.y);
    // Ignore if they are similar
    if(c1 == c2) continue;
    
    int fMax = maxFamilies(componentOfSize,k);
    
    // Case 1
    if(fMax >= f0) {
      s_sol = e.w;
    }
    // Case 2
    if(e.w >= s0) {
      f_sol = max(fMax,f_sol);
    }
    // Update the union find
    uf.link(c1,c2); 
    int c = uf.find_set(c1);
    
    componentOfSize[sizeComponent[c1]]--;
    componentOfSize[sizeComponent[c2]]--;
    sizeComponent[c] = min(k,sizeComponent[c1] + sizeComponent[c2]);
    componentOfSize[sizeComponent[c]] += 1;
    
    n_components--;
    if(n_components == 1) break;
  }
  
  f_sol = max(maxFamilies(componentOfSize,k),f_sol);
  
  cout << s_sol << " " << f_sol << "\n";
  
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
