#include "Generator.hpp"

Generator::Generator() {
  this->addVertex(this->START_WORD);
  this->addVertex(this->END_WORD);
}

void Generator::addEdge(std::string w1, std::string w2) {
  if (!this->isEdge(w1, w2)) {
    if (!this->isVertex(w1))
      this->addVertex(w1);
    if (!this->isVertex(w2))
      this->addVertex(w2);
    vertex* temp1 = this->findVertex(w1);
    vertex* temp2 = this->findVertex(w2);
    std::cout << "Edge - " << w1 << " --> " << w2 << " - created." << std::endl;
  } else {
    edge* temp = this->findEdge(w1, w2);
    temp->count++;
    std::cout << "Edge - " << w1 << " --> " << w2 << " - incremented."
              << std::endl;
  }
}

void Generator::addVertex(std::string w) {
  if (!this->isVertex(w)) {
    vertex v = vertex(w);
    this->vertices.push_back(v);
    std::cout << w << " has been added." << std::endl;
  } else {
    std::cout << w << " is already a vertex." << std::endl;
  }
}

std::string Generator::generateSentence() {
  return "temp";
}

vertex* Generator::findVertex(std::string w) {
  int count = 0;
  for (vertex v : this->vertices) {
    if (v.word == w) {
      return &this->vertices.at(count);
    }
    count++;
  }
  return nullptr;
}

edge* Generator::findEdge(std::string w1, std::string w2) {
  if (this->isVertex(w1) && this->isVertex(w2)) {
    vertex* temp1 = this->findVertex(w1);
    vertex* temp2 = this->findVertex(w2);
    int count = 0;
    for (edge x : temp1->edges) {
      if (x.v == temp2) {
        return &temp1->edges.at(count);
      }
      count++;
    }
  }
  return nullptr;
}

bool Generator::isVertex(std::string w) {
  return this->findVertex(w) != nullptr ? true : false;
}

bool Generator::isEdge(std::string w1, std::string w2) {
  return this->findEdge(w1, w2) != nullptr ? true : false;
}

void Generator::test() {
  this->addVertex(this->START_WORD);
  this->addVertex(this->END_WORD);
  this->addVertex("hello");
  this->addVertex("world");
  this->addVertex("hello");
  vertex* v = this->findVertex("hello");
  vertex* test = this->findVertex("world");
  std::cout << "Vertex: " << v->word << std::endl;
  edge e = edge(test, 1);
  v->edges.push_back(e);
  vertex* t = this->findVertex("hello");
  edge x = v->edges.back();
  std::cout << "Edge Vertex: " << x.v->word << std::endl;
  edge* a = this->findEdge("hello", "world");
  std::cout << "Edge Vertex: " << a->v->word << std::endl;
  this->addEdge("world", "hello");
  this->addEdge("hello", "world");
  edge* t_edge = this->findEdge("hello", "world");
  std::cout << "Edge Count: " << t_edge->count << std::endl;
}
