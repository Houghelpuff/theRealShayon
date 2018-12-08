#include "Generator.hpp"

int main() {
  Generator g;
  g.populate("test.txt");
  g.setProbability();
  std::cout << std::endl;
  while (g.generateSentence().length() > 280)
    ;
  // g.test();
  return 0;
}