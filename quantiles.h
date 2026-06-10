#ifndef QUANTILES_H_
#define QUANTILES_H_

#include <cstddef>
#include <vector>
#include <algorithm>

// Return a quantile 'q' of an array 'd' of size 'size'
template <class T, class F>  // T = numeric type, F = floating point type
T quantile(const T* d, const std::size_t size, F q) {
  // Edge cases
  if (size == 0) return 0;
  if (size == 1) return d[0];
  if (q <= 0) return *std::min_element(d, d + size);
  if (q >= 1) return *std::max_element(d, d + size);

  F float_ind = (size - 1) * q;
  std::size_t ind = std::size_t(float_ind);
  // Floating-point rounding can push float_ind up to size - 1 even
  // though q < 1, which would make the i2 range below empty.
  if (ind >= size - 1) return *std::max_element(d, d + size);
  F delta = float_ind - ind;
  std::vector<T> dcopy(d, d + size);
  std::nth_element(dcopy.begin(), dcopy.begin() + ind, dcopy.end());
  T i1 = *(dcopy.begin() + ind);
  if (delta <= 0) return i1;
  T i2 = *std::min_element(dcopy.begin() + ind + 1, dcopy.end());
  return i1 * (1.0 - delta) + i2 * delta;  // Any value in [i1, i2] is valid.
}

template <class T, class F>
inline T quantile(const std::vector<T>& v, F q)
  { return quantile(v.data(), v.size(), q); }

#endif  // QUANTILES_H_
