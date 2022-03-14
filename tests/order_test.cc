#include <iostream>
#include <cstdlib>
#include <numeric>
#include <string>
#include "ranker.h"
#include "gtest/gtest.h"

namespace {

TEST(OrderTest, Increasing) {
  vector<double> vec = {1, 7, 3, 9, 4};
  const auto orders = order(vec, false);
  ASSERT_EQ(orders, vector<uint_least64_t>({0, 2, 4, 1, 3}));
}

TEST(OrderTest, Decreasing) {
  vector<double> vec = {1, 7, 3, 9, 4};
  const auto orders = order(vec, true);
  ASSERT_EQ(orders, vector<uint_least64_t>({3, 1, 4, 2, 0}));
}

TEST(PartialOrderTest, Increasing) {
  vector<double> vec = {1, 7, 3, 9, 4};
  const auto orders = partial_order(vec, 3, false);
  ASSERT_EQ(orders, vector<uint_least64_t>({0, 2, 4}));
}

TEST(PartialOrderTest, Decreasing) {
  vector<double> vec = {1, 7, 3, 9, 4};
  const auto orders = partial_order(vec, 3, true);
  ASSERT_EQ(orders, vector<uint_least64_t>({3, 1, 4}));
}

}  // namespace
