#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Segment_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Ray_2<K> Ray;
typedef CGAL::Point_2<K> Point;
typedef CGAL::Segment_2<K> Segment;
typedef K::FT FT;

using namespace std;

double floor_to_double(const K::FT& x) {
    double a = std::floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

Point getPoint(Point &start, Ray &ray, Segment &seg) {
  
  auto o = CGAL::intersection(ray,seg);
      
  if(const Point* op = boost::get<Point>(&*o)) {
    return *op;
  }
  
  else if(const Segment *s = boost::get<Segment>(&*o)) {
    Point p1 = s->source();
    Point p2 = s->target();
    
    auto dist1 = CGAL::squared_distance(p1,start);
    auto dist2 = CGAL::squared_distance(p2,start);
    
    return dist1 < dist2 ? p1 : p2;
  }

  return Point(0,0);
}

void solve(int n) {
  
  long int a,b,x,y;
  cin >> a >> b >> x >> y;
  Ray ray = Ray(Point(a,b),Point(x,y));
  Point start = Point(a,b);
  
  vector<Segment> segments(0);
  for(int i = 0; i < n;i++) {
    long int a,b,c,d;
    cin >> a >> b >> c >> d;
    segments.push_back(Segment(Point(a,b),Point(c,d)));
  }
  
  random_shuffle(segments.begin(),segments.end());
  
  bool hit = false;
  Point answer;
  
  int i = 0;
  for(;i < segments.size();i++) {
    if(CGAL::do_intersect(ray,segments [i])) {
      hit = true;
      answer = getPoint(start,ray,segments[i]);
      break;
    }
  }

  if(!hit) {
    cout << "no" << "\n";
    return;
  } 
  
  for(; i < segments.size(); i++) {
    Segment new_ray(start,answer);
    
    if(CGAL::do_intersect(new_ray,segments[i])) {
      answer = getPoint(start,ray,segments[i]);
    }
  }
  cout << setiosflags(ios::fixed) << setprecision(0);
  cout << floor_to_double(answer.x()) << " " << floor_to_double(answer.y()) << "\n";
}

signed main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int n;
  cin >> n;
  
  while(n != 0) {
    solve(n);
    cin >> n;
  }
  
}
