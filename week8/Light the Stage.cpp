#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Point_2<K> Point_2;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;

using namespace std;

typedef struct Participant {
  Point_2 pos;
  int radius;
  int idx;
} Participant;

int h;
int n,m;

vector<Participant> playersLeft(vector<Participant> &participants, vector<Point_2> &lamps, int left,int middle) {
  
  vector<Participant> output(0);

  Triangulation t;
  t.insert(lamps.begin()+left,lamps.begin()+middle);

  int count = 0;
  
  for(int i = 0; i < participants.size();i++) {
    Point_2 nearest_lamp = t.nearest_vertex(participants[i].pos)->point();
    double distance = CGAL::squared_distance(nearest_lamp,participants[i].pos);
    if(distance >= pow(participants[i].radius + h,2)) {
      output.push_back(participants[i]);
    }
  }
  
  return output;
}

void solve() {
  
  cin >> m >> n;
  
  vector<Participant> participants(m);
  for(int i = 0; i < m;i++) {
    int x,y,r;
    cin >> x >> y >> r;
    participants[i] = {Point_2(x,y),r,i};
  }
  
  cin >> h;
  
  vector<Point_2> lamps(n);
  for(int i = 0; i < n;i++) {
    int x,y;
    cin >> x >> y;
    lamps[i] = Point_2(x,y);
  }
  
  int start = 0;
  int end = lamps.size();

  
  while(start < end) {
    int middle = (start + end + 1) / 2;
    auto remainings = playersLeft(participants,lamps,start,middle);

    if(remainings.size() == 0) {
      end = middle-1;
    }
    else {
      start = middle;
      participants = remainings;
    }
  }
  
  for(auto p: participants)
    cout << p.idx << " ";
  
  cout << "\n";
  
  return;  
}

signed main() {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t; cin >> t;
  
  while(t--)
    solve();
    
  return 0;
}
