#ifndef RANKER_H_
#define RANKER_H_

#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;

#ifndef uint
typedef unsigned int uint;
#endif

template <class T>
class lt { public: static int compare(T a, T b) { return(a < b); } };
template <class T>
class gt { public: static int compare(T a, T b) { return(a > b); } };

template <class T, class C>
class ranker {
 private:
  const T* p;
  uint sz;

 public:
  explicit ranker(const vector<T>& v) : p(&v[0]), sz(v.size()) { }
  ranker(const T* tp, uint s) : p(tp), sz(s) { }

  int operator()(uint i1, uint i2) const { return(C::compare(p[i1], p[i2])); }

  vector<uint> get_orders() const {
    vector<uint> orders(sz);
    std::iota(orders.begin(), orders.end(), 0);
    std::sort(orders.begin(), orders.end(), *this);
    return orders;
  }

  vector<uint> get_partial_orders(uint num) const {
    vector<uint> orders(sz);
    if (num > sz) num = sz;
    std::iota(orders.begin(), orders.end(), 0);
    std::partial_sort(orders.begin(), orders.begin() + num, orders.end(), *this);
    orders.resize(num);
    return orders;
  }

  template <class S>
  void get_ranks(vector<S>& w, const string& method) const {
    w.resize(sz);
    auto tmp = get_orders();
    if (method == "average") {
      for (uint c = 0, reps; c < w.size(); c += reps) { reps = 1;
        while (c + reps < w.size() && p[tmp[c]] == p[tmp[c + reps]]) ++reps;
        for (uint k = 0; k < reps; ++k)
          w[tmp[c + k]] = S(2 * c + reps - 1) / 2 + 1;
      }
    } else if (method == "min") {
      for (uint c = 0, reps; c < w.size(); c += reps) { reps = 1;
        while (c + reps < w.size() && p[tmp[c]] == p[tmp[c + reps]]) ++reps;
        for (uint k = 0; k < reps; ++k) w[tmp[c + k]] = c + 1;
      }
    } else if (method == "max") {
      for (uint c = 0, reps; c < w.size(); c += reps) { reps = 1;
        while (c + reps < w.size() && p[tmp[c]] == p[tmp[c + reps]]) ++reps;
        for (uint k = 0; k < reps; ++k) w[tmp[c + k]] = c + reps;
      }
    } else {  // default
      for (uint c = 0; c < w.size(); ++c) w[tmp[c]] = c + 1;
    }
  }

  template <class S>
  void get_partial_ranks(vector<S>& w, const string& method, size_t num) const {
    if (num > sz) num = sz;
    w.resize(sz);
    auto tmp = get_partial_orders(num);
    fill(w.begin(), w.end(), 0);
    if (method == "average") {
      for (uint c = 0, reps; c < num; c += reps) { reps = 1;
        while (c + reps < num && p[tmp[c]] == p[tmp[c + reps]]) ++reps;
        for (uint k = 0; k < reps; ++k)
          w[tmp[c + k]] = S(2 * c + reps - 1) / 2 + 1;
      }
    } else if (method == "min") {
      for (uint c = 0, reps; c < num; c += reps) { reps = 1;
        while (c + reps < num && p[tmp[c]] == p[tmp[c + reps]]) ++reps;
        for (uint k = 0; k < reps; ++k) w[tmp[c + k]] = c + 1;
      }
    } else if (method == "max") {
      for (uint c = 0, reps; c < num; c += reps) { reps = 1;
        while (c + reps < num && p[tmp[c]] == p[tmp[c + reps]]) ++reps;
        for (uint k = 0; k < reps; ++k) w[tmp[c + k]] = c + reps;
      }
    } else {  // default
      for (uint c = 0; c < num; ++c) w[tmp[c]] = c + 1;
    }
  }
};

template <class T, class S>
inline void rank(const vector<T>& v, vector<S>& w,
          const string& method = "average")
  { ranker<T, lt<T> > r(v); r.get_ranks(w, method); }

template <class T, class S>
inline void rank(const T* d, uint size, vector<S>& w,
          const string& method = "average")
  { ranker<T, lt<T> > r(d, size); r.get_ranks(w, method); }

template <class T, class S>
inline void partial_rank(const vector<T>& v, vector<S>& w, uint num,
          const string& method = "average")
  { ranker<T, lt<T> > r(v); r.get_partial_ranks(w, method, num); }

template <class T, class S>
inline void partial_rank(const T* d, uint size, vector<S>& w, uint num,
          const string& method = "average")
  { ranker<T, lt<T> > r(d, size); r.get_partial_ranks(w, method, num); }

template <class T, class S>
inline void order(const vector<T>& v, vector<S>& w)
  { ranker<T, lt<T> > r(v); w = r.get_orders(); }

template <class T, class S>
inline void order(const T* d, uint size, vector<S>& w)
  { ranker<T, lt<T> > r(d, size); w = r.get_orders(); }

template <class T, class S>
inline void partial_order(const vector<T>& v, vector<S>& w, uint num)
  { ranker<T, lt<T> > r(v); w = r.get_partial_orders(num); }

template <class T, class S>
inline void partial_order(const T* d, uint size, vector<S>& w, uint num)
  { ranker<T, lt<T> > r(d, size); w= r.get_partial_orders(num); }

template <class T, class S>
inline void rankhigh(const vector<T>& v, vector<S>& w,
          const string& method = "average")
  { ranker<T, gt<T> > r(v); r.get_ranks(w, method); }

template <class T, class S>
inline void rankhigh(const T* d, uint size, vector<S>& w,
          const string& method = "average")
  { ranker<T, gt<T> > r(d, size); r.get_ranks(w, method); }

template <class T, class S>
inline void partial_rankhigh(const vector<T>& v, vector<S>& w, uint num,
          const string& method = "average")
  { ranker<T, gt<T> > r(v); r.get_partial_ranks(w, method, num); }

template <class T, class S>
inline void partial_rankhigh(const T* d, uint size, vector<S>& w, uint num,
          const string& method = "average")
  { ranker<T, gt<T> > r(d, size); r.get_partial_ranks(w, method, num); }

template <class T, class S>
inline void orderhigh(const vector<T>& v, vector<S>& w)
  { ranker<T, gt<T> > r(v); w = r.get_orders(); }

template <class T, class S>
inline void orderhigh(const T* d, uint size, vector<S>& w)
  { ranker<T, gt<T> > r(d, size); w = r.get_orders(); }

template <class T, class S>
inline void partial_orderhigh(const vector<T>& v, vector<S>& w, uint num)
  { ranker<T, gt<T> > r(v); w = r.get_partial_orders(num); }

template <class T, class S>
inline void partial_orderhigh(const T* d, uint size, vector<S>& w, uint num)
  { ranker<T, gt<T> > r(d, size); w = r.get_partial_orders(num); }

#endif  // RANKER_H_
