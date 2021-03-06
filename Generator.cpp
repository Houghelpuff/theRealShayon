#include "Generator.hpp"
#include <cstdlib>
#include <ctime>
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
    edge e = edge(this->findVertex(w2), 1);
    this->findVertex(w1)->edges.push_back(e);
    // std::cout << "Edge - " << w1 << " --> " << w2 << " - created." <<
    // std::endl;
  } else {
    edge* temp = this->findEdge(w1, w2);
    temp->count++;
    // std::cout << "Edge - " << w1 << " --> " << w2 << " - incremented."
    // << std::endl;
  }
}

void Generator::addVertex(std::string w) {
  if (!this->isVertex(w)) {
    vertex* v = new vertex(w);
    this->vertices.push_back(v);
    // std::cout << w << " has been added." << std::endl;
  } else {
    // std::cout << w << " is already a vertex." << std::endl;
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
        // std::cout << "Prev: " << prevWord << " Curr: " << currWord <<
        // std::endl;
        this->addEdge(prevWord, currWord);
        prevWord = currWord;
      }
      this->addEdge(currWord, this->END_WORD);
    }
  } else {
    std::cout << "ERROR: File " << f << " failed to open." << std::endl;
  }
}

void Generator::setProbability() {
  for (vertex* temp : this->vertices) {
    int prevMax = 0;
    for (int i = 0; i < temp->edges.size(); i++) {
      temp->edges[i].min = prevMax;
      temp->edges[i].max = prevMax + temp->edges[i].count;
      prevMax = temp->edges[i].max;
    }
    temp->maxRange = prevMax;
  }
}

std::string Generator::generateSentence() {
  srand(time(NULL));
  vertex* temp = this->findVertex(this->START_WORD);
  std::vector<std::string> sentence;
  int r = rand() % temp->maxRange;
  for (int i = 0; i < temp->edges.size(); i++) {
    if (r >= temp->edges[i].min && r < temp->edges[i].max) {
      temp = temp->edges[i].v;
      break;
    }
  }

  while (temp->word != this->END_WORD) {
    sentence.push_back(temp->word);
    r = rand() % temp->maxRange;
    for (int i = 0; i < temp->edges.size(); i++) {
      if (r >= temp->edges[i].min && r < temp->edges[i].max) {
        temp = temp->edges[i].v;
        break;
      }
    }
  }
  std::stringstream ss;
  for (std::string s : sentence)
    ss << s << " ";
  std::string generatedSentence = ss.str();
  std::cout << generatedSentence << std::endl;

  std::ofstream file("output.txt", std::ios::out);
  if (file.is_open()) {
    file << generatedSentence;
  }
  return generatedSentence;
}

vertex* Generator::findVertex(std::string w) {
  for (int i = 0; i < this->vertices.size(); i++) {
    if (this->vertices[i]->word == w)
      return this->vertices[i];
  }
  return nullptr;
}

edge* Generator::findEdge(std::string w1, std::string w2) {
  for (int i = 0; i < this->findVertex(w1)->edges.size(); i++) {
    if (this->findVertex(w1)->edges[i].v->word == w2)
      return &this->findVertex(w1)->edges[i];
  }
  return nullptr;
}

bool Generator::isVertex(std::string w) {
  if (this->findVertex(w) == nullptr)
    return false;
  return true;
}

bool Generator::isEdge(std::string w1, std::string w2) {
  if (this->findEdge(w1, w2) == nullptr)
    return false;
  return true;
}

void Generator::test() {
  std::cout << "isVertex test: " << this->isVertex(this->START_WORD)
            << std::endl;
  std::cout << "isVertex test: " << this->isVertex("my") << std::endl;
  std::cout << "isEdge test: " << this->isEdge(this->START_WORD, "my")
            << std::endl;
  vertex* temp = this->findVertex(this->START_WORD);
  for (int i = 0; i < temp->edges.size(); i++) {
    std::cout << temp->word << " --> " << temp->edges[i].v->word
              << " - Min: " << temp->edges[i].min
              << " *** Max: " << temp->edges[i].max << std::endl;
  }
}
