#include <iostream>
#include <cstdlib>
#include <numeric>
#include <string>
#include "ranker.h"
#include "gtest/gtest.h"

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
    uint low_ind = uint(quantile * (v.size() - 1) + 1e-10);
    low_high[0] = vs[low_ind];
    low_high[1] = vs[low_ind + 1];
  }
  return low_high;
}

TEST(QuantilesTest, Base) {
  vector<double> vec(num_elements);
  for (auto& element : vec) {
    element = random() % mod_value;
  }
  for (uint i = 0; i < num_quantiles; ++i) {
    double q = i / ((num_quantiles - 1) * 1.0);
    double quant = quantile(vec, q);
    const auto bounds = quantile_bounds(vec, q);
    // std::cout << bounds[0] << " " << quant << " " << bounds[1] << std::endl;
    EXPECT_LE(bounds[0], quant);
    EXPECT_GE(bounds[1], quant);
  }
}

}  // namespace
