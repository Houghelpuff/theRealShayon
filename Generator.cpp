#include "Generator.hpp"

void Generator::addEdge(std::string w1, std::string w2) {
  if (!this->isEdge(w1, w2)) {
    if (!this->isVertex(w1))
      this->addVertex(w1);
    if (!this->isVertex(w2))
      this->addVertex(w2);
    vertex* temp1 = this->findVertex(w1);
    vertex* temp2 = this->findVertex(w2);
    std::cout << temp1->word << " " << temp2->word << std::endl;
    std::cout << "Edge " << w1 << " --> " << w2 << " created." << std::endl;
  } else {
    edge* temp = this->findEdge(w1, w2);
    temp->count++;
    std::cout << "Edge " << w1 << " --> " << w2 << " incremented." << std::endl;
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
  for (vertex v : this->vertices) {
    if (v.word == w) {
      vertex* temp = new vertex(v.word);
      temp->edges = v.edges;
      return temp;
    }
  }
  return nullptr;
}

edge* Generator::findEdge(std::string w1, std::string w2) {
  if (this->isVertex(w1) && this->isVertex(w2)) {
    vertex* temp1 = this->findVertex(w1);
    vertex* temp2 = this->findVertex(w2);
    for (edge x : temp1->edges) {
      if (x.v->word == w2) {
        edge* e = new edge(temp2, x.count);
        return e;
      }
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
  this->addVertex("hello");
  this->addVertex("world");
  this->addVertex("hello");
  std::cout << this->isVertex("hello") << std::endl;
  vertex* v = this->findVertex("hello");
  vertex* test = this->findVertex("world");
  std::cout << "Vertex: " << v->word << std::endl;
  edge e = edge(test, 1);
  v->edges.push_back(e);
  edge x = v->edges.back();
  std::cout << this->isEdge("hello", "world") << std::endl;
  std::cout << "Edge Vertex: " << x.v->word << std::endl;
  edge* a = this->findEdge("hello", "world");
  std::cout << "Edge Vertex: " << a->v->word << std::endl;
}
