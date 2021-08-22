## ranker
C++ templates to compute ranks, order permutations and quantiles.


### About
- The file [ranker.h](ranker.h) provides templated functions that compute the
  ranks, order permutations and quantiles of the elements of an array or C++
  vector.
- The functions `rank`, `order` and `quantile` are efficient C++
  implementations of R functions with the same name.
- Each of the above functions has a version that ends with `high`
  (e.g., `rankhigh` and `orderhigh`) that compares elements using `>`
  instead of `<`.
- The functions use the C++ standard library `sort` and
  `partial_sort` algorithms in an interesting manner.

### Usage
- `rank(v, w, method)`
  - `v` is an input C++ vector
  - `w` is a numeric C++ vector that will be resized if
  necessary and in which the ranks of the elements
  of `v` get stored.
  - `method` is the optional method used to assign ranks
  when there are ties (see [Details](#details)).
- `rank(a, size, w, method)`
  - `a` is a pointer to an array of length `size`.
  - `w` and `method` are the same as with `rank`.
- `partial_rank(v, w, num, method)`
- `partial_rank(a size, w, num, method)`
  - Similar to `rank`, but these functions compute only
  the ranks of the `num` highest ranked elements and
  assign a rank of 0 to the rest.
- `order(v, w)`
- `order(a, size, w)`
  - `w` is a C++ vector with an integral type that
  stores a permutation that when applied
  to `v` or `a` will sort it.
- partial_order(v, w, num)
  partial_order(a, size, w, num)
  - Similar to `order`, but the permutation is of length
  `num` and only permutes the `num` highest ranked
  elements.
- quantile(v, q)
- quantile(a, size, q)
  Compute the q_th quantile of `v` or` a.

### Details
- method` is an optional string whose value can be
  "average", "min", "max" or "random". If not specified,
  it defaults to "average".
- The elements of` v` or` a` can be any type that can be
  compared using` "<".
- When `method` == `average`, the base type
  of `w` should be a floating point type as the ranks
  can be non-integral. For other methods, the base type
  of `w` can be integral.

### Files:
 - [ranker.h](ranker.h) - A header file containing the functions.
 - [test_rank.cc](test_rank.cc) - A test program using `rank`.
 - [test_partial_rank.cc](test_partial_rank.cc) - A test program using `partial_rank`.
 - [test_quantiles.cc](test_quantiles.cc) - A test program that computes quantiles.
