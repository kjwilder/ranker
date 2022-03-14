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

### Usage (see examples in tests directory)
- `rank(v, method)`
- `rank(a, size, method)`
  - returns a vector of ranks of the elements of `v`.
  - `v` is an input C++ vector
  - `a` is a pointer to an array of length `size`.
  - `method` is the optional method used to assign ranks
    when there are ties (see [Details](#details)).
- `partial_rank(v, num, method)`
- `partial_rank(a size, num, method)`
  - Similar to `rank`, but these functions compute only
    the ranks of the `num` highest ranked elements and
    assign a rank of 0 to the rest.
- `order(v)`
- `order(a, size)`
  - returns a permutation (vector) that when applied
    to `v` or `a` will sort it.
- `partial_order(v, num)`
  `partial_order(a, size, num)`
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
