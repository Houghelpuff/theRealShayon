#include "Generator.hpp"

int main() {
  Generator g;
  g.addVertex("hello");
  g.addVertex("world");
  g.addVertex("hello");
  g.addEdge("hello", "world");
  g.addEdge("hello", "world");
  g.addEdge("world", "hello");
  return 0;
}