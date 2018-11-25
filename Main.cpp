#include "Generator.hpp"

int main() {
  Generator g;
  g.populate("test.txt");
  g.populate("HungerGames.txt");
  g.test();
  return 0;
}