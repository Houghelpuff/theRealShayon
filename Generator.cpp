#include "Generator.hpp"

void Generator::addEdge(std::string w1, std::string w2) {
  if (!this->isEdge(w1, w2)) {
    this->addVertex(w1);
    this->addVertex(w2);
    vertex* temp1 = this->findVertex(w1);
    vertex* temp2 = this->findVertex(w2);
    edge e;
    e.v = temp2;
    e.count++;
    temp1->edges.push_back(e);
    std::cout << "Edge " << w1 << " --> " << w2 << " created." << std::endl;
  } else {
    edge* temp = this->findEdge(w1, w2);
    temp->count++;
    std::cout << "Edge " << w1 << " --> " << w2 << " incremented." << std::endl;
  }
}

void Generator::addVertex(std::string w) {
  if (!this->isVertex(w)) {
    vertex v;
    v.word = w;
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
      vertex* temp = &v;
      return temp;
    }
  }
  return nullptr;
}

edge* Generator::findEdge(std::string w1, std::string w2) {
  vertex* temp = this->findVertex(w1);
  if (temp != nullptr) {
    for (edge x : temp->edges) {
      if (x.v->word == w2) {
        edge* e = &x;
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
