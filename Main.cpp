#include "Generator.hpp"

int main() {
  Generator g;
  g.populate("test.txt");
  g.test();
  return 0;
}