#include <iostream>
#include <cstdlib>
#include <numeric>
#include <string>
#include <vector>
#include "quantiles.h"
#include "gtest/gtest.h"

using std::vector;

const int num_elements = 100;
const int num_quantiles = 20;
const int mod_value = 80;

namespace {

vector<double> quantile_bounds(const vector<double>& v, double quantile) {
  vector<double> low_high = vector<double>(2);
  auto vs = v;
  sort(vs.begin(), vs.end());
  if (quantile <= 0.0) {
    low_high[0] = -DBL_MAX;
    low_high[1] = vs[0];
  } else if (quantile >= 1.0) {
    low_high[0] = vs[v.size() - 1];
    low_high[1] = DBL_MAX;
  } else {
    unsigned int low_ind = (unsigned int)(quantile * (v.size() - 1) + 1e-10);
    low_high[0] = vs[low_ind];
    low_high[1] = vs[low_ind + 1];
  }
  return low_high;
}

TEST(QuantilesTest, Baseline) {
  vector<double> vec(num_elements);
  for (auto& element : vec) {
    element = random() % mod_value;
  }
  for (auto i = 0; i < num_quantiles; ++i) {
    double q = i / ((num_quantiles - 1) * 1.0);
    double quant = quantile(vec, q);
    const auto bounds = quantile_bounds(vec, q);
    // std::cout << bounds[0] << " " << quant << " " << bounds[1] << std::endl;
    EXPECT_LE(bounds[0], quant);
    EXPECT_GE(bounds[1], quant);
  }
}

template<class T>
void base_expects(const vector<T>& vec) {
  for (auto i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(i, quantile(vec, 1.0 * i / (vec.size() - 1)));
  }
}
TEST(QuantilesTest, Thirds) {
  vector<int> vec = {0, 1, 2, 3};
  base_expects(vec);
  EXPECT_EQ(1, quantile(vec, 0.5));
}

TEST(QuantilesTest, DoubleThirds) {
  vector<double> vec = {0, 1, 2, 3};
  base_expects(vec);
  EXPECT_EQ(1.5, quantile(vec, 0.5));
}

TEST(QuantilesTest, Sevenths) {
  vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7};
  base_expects(vec);
}

TEST(QuantilesTest, DoubleSevenths) {
  vector<double> vec = {0, 1, 2, 3, 4, 5, 6, 7};
  base_expects(vec);
}

}  // namespace
