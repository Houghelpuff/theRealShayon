#include "Generator.hpp"

int main() {
  Generator g;
  g.populate("test.txt");
  g.setProbability();
  g.generateSentence();
  g.test();
  return 0;
}