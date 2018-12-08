#include "Generator.hpp"

int main() {
  Generator g;
  g.populate("test.txt");
  g.setProbability();
  std::cout << std::endl;
  g.generateSentence();
  // g.test();
  return 0;
}