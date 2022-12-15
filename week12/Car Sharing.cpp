#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

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

void solve()
{
  int N,S;
  cin >> N >> S;
  
  const int max_price = 100;
  const int max_cars = 10000;
  
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
  
  set<int> s = set<int>();
  for(int i = 0; i < N;i++) {
    s.insert(requests[i].departure);
    s.insert(requests[i].arrival);
  }
  
  int size = s.size();
  
  map<int,int> translate;
  int counter = 0;
  for(auto e : s) {
    translate[e] = counter++;
  }
  
  graph G(size*S);
  edge_adder adder(G);
    
  auto v_source = boost::add_vertex(G);
  auto v_sink = boost::add_vertex(G);
  
  for(int i = 0; i < size-1; i++) {
    for(int j = 0; j < S;j++) {
      adder.add_edge(i*S + j,(i+1)*S + j,max_cars,max_price);
    } 
  }
  
  for(int j = 0; j < S;j++) {
    adder.add_edge(v_source,j,cars[j],max_price);
    adder.add_edge((size-1)*S + j,v_sink,max_cars,max_price);
  }
  
  for(int i = 0; i < N;i++) {
    auto req = requests[i];
    int from = translate[req.departure];
    int to = translate[req.arrival];
    int j1 = req.from;
    int j2 = req.to;
    int price = (to-from)*max_price - req.profit;
    adder.add_edge(from*S + j1,to*S + j2,1,price);
  }
  
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  long flow = boost::find_flow_cost(G);
  flow = max_price * nb_cars * (size+1) - flow;
  cout << flow << endl;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0); 
  
  int t; 
  cin >> t;
    
  while(t--)
    solve();
    
  return 0;
}
