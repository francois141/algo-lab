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

## CGAL

## Techniques