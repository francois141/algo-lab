# ALGO Lab ETHZ 2022

## STL

#### Sort an array

```c++
sort(array.begin(),array.end(), [](const int &e1, const int &e2) -> bool {
    return e1 < e2;
});
```

#### Sum of all elements in an array

```c++
int sum = accumulate(array.begin(),array.end(),0);
```

#### Prefix sum with stl

```c++
partial_sum(array.begin(),array.end(),array.begin());
```

#### Shuffles all values in an array (avoid adversary input)

```c++
random_shuffle(array.begin(),array.end());
```

#### Check if an elements is in array (must be sorted)

```c++
bool present = binary_search(array.begin(),array.end(), element);
```

#### Find first element bigger equal value (must be sorted)

This return an iterator. We use * to dereference the iterator.

```c++
int returned_value = *min_value(array.begin(),array.end(),value);   
```

#### Find first element bigger than value (must be sorted)

This return an iterator. We use * to dereference the iterator.

```c++
int returned_value = *max_value(array.begin(),array.end(),value);   
```

#### Intersection of two sets

```c++
std::vector<int> v_intersection;
std::set_intersection(array1.begin(), array1.end(), array2.begin(), array2.end(), std::back_inserter(v_intersection));
```

#### Union of two sets

```c++
std::vector<int> v_union;
std::set_union(array1.begin(), array1.end(), array2.begin(), array2.end(), std::back_inserter(v_union));
```
## Boost

### Basics

#### Declaration of graphs

```cpp 
#include <boost/graph/adjacency_list.hpp>

// Create undirected graph
typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::undirectedS> graph;

// Create directed graph
typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::directedS> graph;

// Create directed weighted graph
typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::directedS,boost::no_property, boost::property<boost::edge_weight_t, int> > weighted_graph;
```

#### Manipulation of edges with propery map
```cpp 
// Graph
typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::undirectedS,boost::no_property,boost::property<boost::edge_weight_t,int>> graph;

// Iterator over descriptor
typedef boost::graph_traits<graph>::edge_iterator edge_it;

// Descriptor
typedef boost::graph_traits<graph>::edge_descriptor edge_descriptor;

// Edge weight
typedef boost::property_map<graph,boost::edge_weight_t>::type edge_weights_map;

// Retrieve the property map
edge_weights_map edge_map = get(boost::edge_weight,G);

edge_it e_beg, e_end;
for (boost::tie(e_beg, e_end) = boost::edges(G); e_beg != e_end; ++e_beg) {
    // Output from & to
    std::cout << boost::source(*e_beg, G) << " " << boost::target(*e_beg, G) << "\n";
    // Output weight of the edge
    std::cout << edge_map[*e_beg] << "\n"; 
}

```

#### Iterator over all edges from a single vertex

```cpp
// Graph
typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::undirectedS,boost::no_property,boost::property<boost::edge_weight_t,int>> graph;

// Iterator over descriptor
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;

out_edge_it e_beg, e_end;
for (boost::tie(e_beg, e_end) = boost::out_edges(G); e_beg != e_end; ++e_beg) {
    std::cout << boost::target(*e_beg, G) << "\n";

}
```

### Algorithms

#### Dijkstra - shortest path from one node to all other in the graph

```cpp

#include <boost/graph/dijkstra_shortest_paths.hpp>

std::vector<int> dijkstra_dist(const weighted_graph &G, int s, int t) {
    int n = boost::num_vertices(G);
    std::vector<int> dist_map(n);

    boost::dijkstra_shortest_paths(G, s,boost::distance_map(boost::make_iterator_property_map(dist_map.begin(),boost::get(boost::vertex_index, G))));

    return dist_map;
}

```

#### MST - Kruskal algorithm

```cpp

#include <boost/graph/kruskal_min_spanning_tree.hpp>

vector<edge_desc> kruskal(const weighted_graph &G) {
    std::vector<edge_desc> mst;

    boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));

    return mst;
}
```


#### Maximum matching

```cpp

#include <boost/graph/max_cardinality_matching.hpp>

int maximum_matching(const graph &G) {
    int n = boost::num_vertices(G);
    std::vector<vertex_desc> mate_map(n); 

    const vertex_desc NULL_VERTEX = boost::graph_traits<graph>::null_vertex();

    boost::edmonds_maximum_cardinality_matching(G, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
    int matching_size = boost::matching_size(G, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

    return matching_size;
}

```

#### Bipartitness of a graph

```cpp
bool is_bipartite = boost::is_bipartite(G); 
```

#### Connected components

```cpp

#include <boost/graph/connected_components.hpp>

void strong_connected_comp(const graph &G) {
    int n = boost::num_vertices(G);

    std::vector<int> scc_map(n); 
    int nscc = boost::connected_components(G,boost::make_iterator_property_map(scc_map.begin(), boost::get(boost::vertex_index, G)));

    std::cout << "Number of connected components: " << nscc << "\n";
    for (int i = 0; i < n; ++i) {
        std::cout << i << " " << scc_map[i] << "\n";
    }
}
```


#### Strongly connected components

```cpp

#include <boost/graph/strong_components.hpp>

void strong_connected_comp(const graph &G) {
    int n = boost::num_vertices(G);

    std::vector<int> scc_map(n); 
    int nscc = boost::strong_components(G,boost::make_iterator_property_map(scc_map.begin(), boost::get(boost::vertex_index, G)));

    std::cout << "Number of connected components: " << nscc << "\n";
    for (int i = 0; i < n; ++i) {
        std::cout << i << " " << scc_map[i] << "\n";
    }
}
```

## CGAL

### Basics

#### Kernels

```cpp
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
```

#### Basics types

```cpp
typedef K::Point_2 Point;
typedef K::Line_2 Line;
typedef K::Ray_2 Ray;
typedef K::Triangle_2 Triangle;
typedef K::Circle_2 Circle;
typedef K::FT FT;

Point point = Point(x,y);
Line line = Line(p1, p2);
Ray ray = Ray(start_point, direction);
Triangle triangle = Triangle(p1,p2,p3);
Circle circle = Circle(c1,c2,c3);
```

#### Intersections & distance

```cpp

// Check for intersection
if (CGAL::do_intersect(s[i],s[j])) {
    // Compute intersection
    auto o = CGAL::intersection(s[i],s[j]);
    if (const Point* op = boost::get<Point>(&*o))
        std::cout << "point: " << *op << "\n";
    else if (const Segment* os = boost::get<Segment>(&*o))
        std::cout << "segment: " << os->source() << " " << os->target() << "\n";
    else 
        throw std::runtime_error("strange segment intersection");
}

// Get distance between two points
auto distance = CGAL::squared_distance(p1,p2);
```

#### Get minimum enclosing cercle

```cpp

#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

Min_circle mc(Points.begin(), Points.end(), true);

Traits::Circle c = mc.circle();
std::cout << c.center() << " " << c.squared_radius() << "\n";
```

#### Ceil & floor

```cpp
double floor_to_double(const K::FT& x)
{
    double a = std::floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

double ceil_to_double(const K::FT& x)
{
    double a = std::ceil(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}
```

### Algorithms

## Techniques

## LP

## Flows