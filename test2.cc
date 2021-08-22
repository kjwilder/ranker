#include <iostream>
#include <cstdlib>
#include <string>
#include "./ranker.h"

int main(int argc, char** argv) {
  uint num1 = 10, num2 = 5, dump = 1;
  string method = "average";  // Can also be "min" or "max" or "default"
  if (argc > 1) num1 = (uint) atol(argv[1]);
  if (argc > 2) num2 = (uint) atol(argv[2]);
  if (argc > 3) method = argv[3];
  if (argc > 4) dump = (uint) atol(argv[4]);
  std::cerr << "Running: [" << argv[0]
       << " num1=" << num1 << " num2=" << num2 << " method=" << method
       << " dump=" << dump << "]" << std::endl;

  vector<double> b(num1);
  for (uint i = 0; i < num1; ++i)
    b[i] = arc4random() % 8;

  vector<double> ranks;
  partial_rank(b, ranks, num2, method);
  if (dump) {
    for (uint i = 0; i < ranks.size(); ++i) {
      std::cout << b[i] << " " << ranks[i] << std::endl;
    }
  }

  /*
  std::cout << std::endl << std::endl;
  vector<int> orders;
  partial_order(b, orders, num2);
  if (dump)
    for (uint i = 0; i < orders.size(); ++i)
      std::cout << b[i] << " " << orders[i] << std::endl;
    for (uint i = orders.size(); i < b.size(); ++i)
      std::cout << b[i] << " " << 0 << std::endl;
  */

  return 0;
}
