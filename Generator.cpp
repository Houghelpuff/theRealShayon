#include "Generator.hpp"

void Generator::addEdge(std::string w1, std::string w2) {}

void Generator::addVertex(std::string w) {
  if (!this->findVertex(w)) {
    vertex v;
    v.word = w;
    this->vertices.push_back(v);
  } else {
    std::cout << w << " is already a vertex." << std::endl;
  }
}

std::string Generator::generateSentence() {
  return "temp";
}

vertex* Generator::findVertex(std::string w) {
  for (vertex v : this->vertices) {
    if (v.word == w)
      return &v;
  }
  return nullptr;
}

bool Generator::isVertex(std::string w) {
  return this->findVertex(w) != nullptr ? true : false;
}

bool Generator::isEdge(std::string w1, std::string w2) {
  vertex* temp = this->findVertex(w1);
  if (temp != nullptr) {
    for (edge x : temp->edges) {
      if (x.v->word == w2) {
        return true;
      }
    }
  }
  return false;
}
