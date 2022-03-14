## ranker
C++ templates to compute ranks, order permutations and quantiles.

### About
- This repo contains header files that provide templated functions that compute
  the ranks, order permutations and quantiles of the elements of an array or
  C++ vector.
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
- `partial_order(v, w, num)`
  `partial_order(a, size, w, num)`
  - Similar to `order`, but the permutation is of length
    `num` and only permutes the `num` highest ranked
    elements.
- `quantile(v, q)`
- `quantile(a, size, q)`
  - Compute the `q_th` quantile of `v` or `a`.

### Details
- `method` is an optional string whose value can be
  `average`, `min`, `max` or `random`. If not specified,
  it defaults to `average`.
- When `method` == `average`, the ranks may be non-integral.

### Tests
- `bazel test :all`
