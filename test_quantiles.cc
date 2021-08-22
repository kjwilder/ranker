#include <iostream>
#include <cstdlib>
#include <string>
#include "./ranker.h"

int main(int argc, char** argv) {
  uint num = 10, div = 10, dump = 1;
  string method = "average";  // Can also be "min" or "max" or "default"
  if (argc > 1) num = (uint) atol(argv[1]);
  if (argc > 2) div = (uint) atol(argv[2]);
  if (argc > 3) dump = (uint) atol(argv[3]);
  std::cerr << "Running: [" << argv[0]
       << " num=" << num << " div=" << div
       << " dump=" << dump << "]" << std::endl;

  vector<double> b(num);
  for (uint i = 0; i < num; ++i) {
    b[i] = i;
    std::cout << b[i] << std::endl;
  }

  for (uint i = 0; i <= div; ++i)
    std::cout << "Quantile " << i / (div * 1.0) << ": "
      << quantile(b, i / (div * 1.0)) << std::endl;

  return 0;
}
