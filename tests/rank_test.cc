#include <iostream>
#include <cstdlib>
#include <numeric>
#include <string>
#include "ranker.h"
#include "gtest/gtest.h"

namespace {

TEST(RankerTest, Less) {
  vector<double> vec = {1, 7, 3, 9, 4};
  const auto ranks = rank(vec, "average", false);
  ASSERT_EQ(ranks, vector<double>({1, 4, 2, 5, 3}));
}

TEST(RankerTest, Greater) {
  vector<double> vec = {1, 7, 3, 9, 4};
  const auto ranks = rank(vec, "average", true);
  ASSERT_EQ(ranks, vector<double>({5, 2, 4, 1, 3}));
}

TEST(RankerTest, Min) {
  vector<double> vec = {1, 7, 3, 3, 4};
  const auto ranks = rank(vec, "min");
  ASSERT_EQ(ranks, vector<double>({1, 5, 2, 2, 4}));
}

TEST(RankerTest, Max) {
  vector<double> vec = {1, 7, 3, 3, 4};
  const auto ranks = rank(vec, "max");
  ASSERT_EQ(ranks, vector<double>({1, 5, 3, 3, 4}));
}

vector<double> explicit_ranker(const vector<double>& v, const string& m) {
  vector<double> ranks(v.size());
  double max = *std::max_element(v.begin(), v.end());
  vector<double> counts(max + 1);
  for (const auto vals : v) {
    counts[vals]++;
  }
  vector<double> cum_counts(max + 1);
  std::partial_sum(counts.begin(), counts.end(), cum_counts.begin());
  vector<double> rank_values(cum_counts.size());
  if (m == "average") {
    for (int i = 1; i < rank_values.size(); ++i) {
      rank_values[i] = (cum_counts[i - 1] + cum_counts[i] + 1.0) / 2.0;
    }
    rank_values[0] = cum_counts[0] / 2.0 + 0.5;
  } else if (m == "min") {
    rank_values[0] = 1;
    for (int i = 1; i < rank_values.size(); ++i) {
      rank_values[i] = cum_counts[i - 1] + 1;
    }
  } else if (m == "max") {
    rank_values = cum_counts;
  }
  for (int i = 0; i < ranks.size(); ++i) {
    ranks[i] = rank_values[v[i]];
  }
  return ranks;
}

void test_suite(const string& m) {
  const int num_elements = 20;
  const int mod_value = 10;
  const int num_iterations = 20;
  vector<double> vec(num_elements);
  for (int iter = 0; iter < num_iterations; ++iter) {
    for (unsigned int i = 0; i < vec.size(); ++i) {
      vec[i] = random() % mod_value;
    }
    const auto ranks = rank(vec, m);
    const auto explicit_ranks = explicit_ranker(vec, m);
    ASSERT_EQ(ranks.size(), explicit_ranks.size());
    for (int i = 0; i < ranks.size(); ++i) {
      EXPECT_EQ(ranks[i], explicit_ranks[i])
        << "Mismatch at position " << i << std::endl;
    }
  }
}

TEST(RankerTest, SuiteAverage) {
  test_suite("average");
}

TEST(RankerTest, SuiteMin) {
  test_suite("min");
}

TEST(RankerTest, SuiteMax) {
  test_suite("max");
}

TEST(RankerTest, SuiteRandom) {
  // test_suite("random");
}

}  // namespace
