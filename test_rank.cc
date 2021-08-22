#include <iostream>
#include <cstdlib>
#include <string>
#include "./ranker.h"

int main(int argc, char** argv) {
  uint num = 10, dump = 1;
  string method = "average";  // Can also be "min" or "max" or "default"
  if (argc > 1) num = (uint) atol(argv[1]);
  if (argc > 2) method = argv[2];
  if (argc > 3) dump = (uint) atol(argv[3]);
  std::cerr << "Running: [" << argv[0]
       << " num=" << num << " method=" << method
       << " dump=" << dump << "]" << std::endl;

  vector<double> b(num);
  for (uint i = 0; i < num; ++i)
    b[i] = arc4random() % 8;

  vector<double> ranks;
  rank(b, ranks, method);
  if (dump) {
    for (uint i = 0; i < ranks.size(); ++i) {
      std::cout << b[i] << " " << ranks[i] << std::endl;
    }
  }

  std::cout << std::endl;

  rankhigh(b, ranks, method);
  if (dump) {
    for (uint i = 0; i < ranks.size(); ++i) {
      std::cout << b[i] << " " << ranks[i] << std::endl;
    }
  }

  return 0;
}
