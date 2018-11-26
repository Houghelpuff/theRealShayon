#include "Generator.hpp"
#include <fstream>
#include <sstream>

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
    edge e = edge(temp2, 1);
    temp1->edges.push_back(e);
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

void Generator::populate(std::string f) {
  std::ifstream file(f);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line, '\n')) {
      std::stringstream ss;
      ss << line;
      std::string prevWord = this->START_WORD;
      std::string currWord;
      while (std::getline(ss, currWord, ' ')) {
        this->addEdge(prevWord, currWord);
        prevWord = currWord;
      }
      this->addEdge(currWord, this->END_WORD);
    }
  } else {
    std::cout << "ERROR: File " << f << " failed to open." << std::endl;
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
      if (x.v->word == w2) {
        return &this->findVertex(w1)->edges.at(count);
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
  vertex* v = this->findVertex(this->START_WORD);
  std::cout << "Edges Vector Size: " << v->edges.size() << std::endl;
  for (edge e : v->edges)
    std::cout << e.v->word << " - " << e.count << std::endl;
}
