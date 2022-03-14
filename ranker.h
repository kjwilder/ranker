#ifndef RANKER_H_
#define RANKER_H_

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

using std::vector;
using std::string;

template <class T, typename C>
class ranker {
 private:
  const T* p;
  uint_least64_t sz;
  std::function<bool(const T&, const T&)> comp;

 public:
  explicit ranker(const vector<T>& v) : p(&v[0]), sz(v.size()), comp(C()) { }
  ranker(const T* tp, uint_least64_t s) : p(tp), sz(s), comp(C()) { }

  int operator()(uint_least64_t i1, uint_least64_t i2) const {
    return comp(p[i1], p[i2]);
  }

  vector<uint_least64_t> get_orders() const {
    vector<uint_least64_t> orders(sz);
    std::iota(orders.begin(), orders.end(), 0);  // Fill with 0, ..., sz - 1
    std::sort(orders.begin(), orders.end(), *this);
    return orders;
  }

  vector<uint_least64_t> get_partial_orders(uint_least64_t num) const {
    vector<uint_least64_t> orders(sz);
    if (num > sz) num = sz;
    std::iota(orders.begin(), orders.end(), 0);  // Fill with 0, ..., sz - 1
    std::partial_sort(
        orders.begin(), orders.begin() + num, orders.end(), *this);
    orders.resize(num);
    return orders;
  }

  vector<double> get_ranks(const string& method) const {
    vector<double> ranks(sz);  // Usually should be uint_least64_t.
    auto tmp = get_orders();
    if (method == "average") {
      for (uint_least64_t c = 0, reps; c < ranks.size(); c += reps) {
        reps = 1;
        while (c + reps < ranks.size() && p[tmp[c]] == p[tmp[c + reps]]) ++reps;
        for (uint_least64_t k = 0; k < reps; ++k)
          ranks[tmp[c + k]] = static_cast<double>(2 * c + reps - 1) / 2 + 1;
      }
    } else if (method == "min") {
      for (uint_least64_t c = 0, reps; c < ranks.size(); c += reps) {
        reps = 1;
        while (c + reps < ranks.size() && p[tmp[c]] == p[tmp[c + reps]]) ++reps;
        for (uint_least64_t k = 0; k < reps; ++k) ranks[tmp[c + k]] = c + 1;
      }
    } else if (method == "max") {
      for (uint_least64_t c = 0, reps; c < ranks.size(); c += reps) {
        reps = 1;
        while (c + reps < ranks.size() && p[tmp[c]] == p[tmp[c + reps]]) ++reps;
        for (uint_least64_t k = 0; k < reps; ++k) ranks[tmp[c + k]] = c + reps;
      }
    } else {  // default
      for (uint_least64_t c = 0; c < ranks.size(); ++c) ranks[tmp[c]] = c + 1;
    }
    return ranks;
  }

  vector<double> get_partial_ranks(
      const string& method, uint_least64_t num) const {
    vector<double> ranks(sz);
    if (num > sz) num = sz;
    auto tmp = get_partial_orders(num);
    if (method == "average") {
      for (uint_least64_t c = 0, reps; c < num; c += reps) {
        reps = 1;
        while (c + reps < num && p[tmp[c]] == p[tmp[c + reps]]) ++reps;
        for (uint_least64_t k = 0; k < reps; ++k)
          ranks[tmp[c + k]] = static_cast<double>(2 * c + reps - 1) / 2 + 1;
      }
    } else if (method == "min") {
      for (uint_least64_t c = 0, reps; c < num; c += reps) {
        reps = 1;
        while (c + reps < num && p[tmp[c]] == p[tmp[c + reps]]) ++reps;
        for (uint_least64_t k = 0; k < reps; ++k) ranks[tmp[c + k]] = c + 1;
      }
    } else if (method == "max") {
      for (uint_least64_t c = 0, reps; c < num; c += reps) {
        reps = 1;
        while (c + reps < num && p[tmp[c]] == p[tmp[c + reps]]) ++reps;
        for (uint_least64_t k = 0; k < reps; ++k) ranks[tmp[c + k]] = c + reps;
      }
    } else {  // default
      for (uint_least64_t c = 0; c < num; ++c) ranks[tmp[c]] = c + 1;
    }
    return ranks;
  }
};

template <class T>
inline vector<double> rank(const vector<T>& v,
    const string& method = "average", bool decreasing = false) {
  if (decreasing) {
    return ranker<T, std::greater<T>>(v).get_ranks(method);
  } else {
    return ranker<T, std::less<T>>(v).get_ranks(method);
  }
}

template <class T>
inline vector<double> rank(const T* d, uint_least64_t size,
    const string& method = "average", bool decreasing = false) {
  if (decreasing) {
    return ranker<T, std::greater<T>>(d, size).get_ranks(method);
  } else {
    return ranker<T, std::less<T>>(d, size).get_ranks(method);
  }
}

template <class T>
inline vector<double> partial_rank(const vector<T>& v, uint_least64_t num,
    const string& method = "average", bool decreasing = false) {
  if (decreasing) {
    return ranker<T, std::greater<T>>(v).get_partial_ranks(method, num);
  } else {
    return ranker<T, std::less<T>>(v).get_partial_ranks(method, num);
  }
}

template <class T>
inline vector<double> partial_rank(const T* d, uint_least64_t size,
    uint_least64_t num,
    const string& method = "average", bool decreasing = false) {
  if (decreasing) {
    return ranker<T, std::greater<T>>(d, size).get_partial_ranks(method, num);
  } else {
    return ranker<T, std::less<T>>(d, size).get_partial_ranks(method, num);
  }
}

template <class T>
inline vector<uint_least64_t> order(
    const vector<T>& v, bool decreasing = false) {
  if (decreasing) {
    return ranker<T, std::greater<T>>(v).get_orders();
  } else  {
    return ranker<T, std::less<T>>(v).get_orders();
  }
}

template <class T>
inline vector<uint_least64_t> order(const T* d, uint_least64_t size,
    bool decreasing = false) {
  if (decreasing) {
    return ranker<T, std::greater<T>>(d, size).get_orders();
  } else  {
    return ranker<T, std::less<T>>(d, size).get_orders();
  }
}

template <class T>
inline vector<uint_least64_t> partial_order(const vector<T>& v,
    uint_least64_t num, bool decreasing = false) {
  if (decreasing) {
    return ranker<T, std::greater<T>>(v).get_partial_orders(num);
  } else  {
    return ranker<T, std::less<T>>(v).get_partial_orders(num);
  }
}

template <class T>
inline vector<uint_least64_t> partial_order(const T* d, uint_least64_t size,
    uint_least64_t num, bool decreasing = false) {
  if (decreasing) {
    return ranker<T, std::greater<T>>(d, size).get_partial_orders(num);
  } else  {
    return ranker<T, std::less<T>>(d, size).get_partial_orders(num);
  }
}

#endif  // RANKER_H_
