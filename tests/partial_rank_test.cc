#include <iostream>
#include <cstdlib>
#include <numeric>
#include <string>
#include "ranker.h"
#include "gtest/gtest.h"

// test partial_rank and partial_order

namespace {

TEST(PartialRankerTest, Less) {
  vector<double> vec = {1, 7, 3, 9, 4};
  const auto ranks = partial_rank(vec, 3, "average", "less");
  ASSERT_EQ(ranks, vector<double>({1, 0, 2, 0, 3}));
}

TEST(PartialRankerTest, Greater) {
  vector<double> vec = {1, 7, 3, 9, 4};
  const auto ranks = partial_rank(vec, 3, "average", "greater");
  ASSERT_EQ(ranks, vector<double>({0, 2, 0, 1, 3}));
}

TEST(PartialRankerTest, Min) {
  vector<double> vec = {1, 7, 3, 3, 4};
  const auto ranks = partial_rank(vec, 3, "min");
  ASSERT_EQ(ranks, vector<double>({1, 0, 2, 2, 0}));
}

TEST(PartialRankerTest, Max) {
  vector<double> vec = {1, 7, 3, 3, 4};
  const auto ranks = partial_rank(vec, 3, "max");
  ASSERT_EQ(ranks, vector<double>({1, 0, 3, 3, 0}));
}

vector<double> explicit_ranker(
    const vector<double>& v, unsigned int partials, const string& m) {
  vector<double> ranks(v.size());
  double max = *std::max_element(v.begin(), v.end());
  vector<double> counts(max + 1);
  for (const auto vals : v) {
    counts[vals]++;
  }
  vector<double> cum_counts(max + 1);
  std::partial_sum(counts.begin(), counts.end(), cum_counts.begin());
  for (int i = 0; i < cum_counts.size(); ++i) {
    if (cum_counts[i] > partials) {
      cum_counts[i] = partials;
    }
  }
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
    for (int i = 0; i < rank_values.size(); ++i) {
      rank_values[i] = cum_counts[i];
    }
  }
  for (int i = 0; i < ranks.size(); ++i) {
    ranks[i] = rank_values[v[i]];
  }
  return ranks;
}

void partial_ranker_test(const string& m) {
  const int test_vector_size = 200;
  const int max_value = 10;
  const int num_partial_ranks = 8;
  vector<double> vec(test_vector_size);
  for (uint i = 0; i < vec.size(); ++i) {
    vec[i] = random() % max_value;
  }
  const auto ranks = partial_rank(vec, num_partial_ranks, m);
  const auto explicit_ranks = explicit_ranker(vec, num_partial_ranks, m);
  ASSERT_EQ(ranks.size(), explicit_ranks.size());
  double num_non_zero = 0.0;
  for (int i = 0; i < ranks.size(); ++i) {
    if (ranks[i] != 0) {
      EXPECT_EQ(ranks[i], explicit_ranks[i])
        << "Mismatch at position " << i << std::endl;
      num_non_zero++;
    }
  }
  EXPECT_EQ(num_non_zero, num_partial_ranks);
}

TEST(PartialRankerTest, SuiteAverage) {
  partial_ranker_test("average");
}

TEST(PartialRankerTest, SuiteMin) {
  partial_ranker_test("min");
}

TEST(PartialRankerTest, SuiteMax) {
  partial_ranker_test("max");
}

TEST(PartialRankerTest, SuiteRandom) {
  // partial_ranker_test("random")
}

}  // namespace
