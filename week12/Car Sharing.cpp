#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

#define int long

using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                              boost::property<boost::edge_residual_capacity_t, long,
                              boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                              boost::property<boost::edge_weight_t, long>>>>> graph;
                              
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it; 

class edge_adder
{
  graph &G;

public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost)
  {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;      // new assign cost
    w_map[rev_e] = -cost; // new negative cost
  }
};

struct request {
  int from;
  int to;
  int departure;
  int arrival;
  int profit;
};

vector<map<int,int>> compressed;
vector<int> prefix;

void insert(int station, int time) {
  if(compressed[station].find(time) == compressed[station].end()) {
    compressed[station][time] = compressed[station].size();
  }
}

int getIndex(int station, int time) {
  return prefix[station] + compressed[station][time];
}

void solve()
{
  int N,S;
  cin >> N >> S;
  
  const int max_profit  = 100;
  const int max_time = INT_MAX / 8;
  
  vector<int> cars = vector<int>(S);
  for(int i = 0; i < S;i++) {
    cin >> cars[i];
  }
  
  int nb_cars = accumulate(cars.begin(),cars.end(),0);
  
  vector<request> requests = vector<request>(N);
  for(int i = 0; i < N;i++){
    cin >> requests[i].from;
    cin >> requests[i].to;
    cin >> requests[i].departure;
    cin >> requests[i].arrival;
    cin >> requests[i].profit;
    requests[i].from--;
    requests[i].to--;
  }
  
  compressed = vector<map<int,int>>(S);
  
  for(int i = 0; i < N;i++) {
    auto req = requests[i];
    insert(req.from,req.departure);
    insert(req.to,req.arrival);
  }
  
  prefix = vector<int>(S);
  for(int i = 1; i < S;i++) {
    prefix[i] = prefix[i-1] + compressed[i-1].size();
  }
  
  graph G(prefix[S-1] + compressed[S-1].size());
  edge_adder adder(G);
  
  auto v_source = boost::add_vertex(G);
  auto v_sink = boost::add_vertex(G);
  
  // Setup graph for stations
  for(int i = 0; i < S; i++) {
    if(compressed[i].size() == 0) continue;
    auto it = compressed[i].begin();
    int prev_time = it->first;
    adder.add_edge(v_source,getIndex(i,prev_time),cars[i], (prev_time) * max_profit);
    
    it++;
    for(; it != compressed[i].end(); ++it) {
      int curr_time = it->first;
      adder.add_edge(getIndex(i,prev_time), getIndex(i, curr_time), INT_MAX, (curr_time - prev_time) * max_profit);
      prev_time = curr_time;
    }
    
    adder.add_edge(getIndex(i,prev_time),v_sink, INT_MAX, (max_time - prev_time) * max_profit);
  }
  
  // Setup requests right now 
  for(const auto &req: requests) {
    adder.add_edge(getIndex(req.from,req.departure),getIndex(req.to,req.arrival),1,(req.arrival - req.departure) * max_profit - req.profit);
  }
  
  int flow = boost::push_relabel_max_flow(G,v_source,v_sink);
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  int cost = boost::find_flow_cost(G);

  cout << flow * max_time * max_profit - cost << "\n";
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
