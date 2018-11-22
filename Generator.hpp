#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <iostream>
#include <vector>

struct vertex;

/*
The edge struct is used to create links between one vertex and it's
following vertex.
Properties:
  - vertex* v -- the vertex of the word following the current word
                EX: 'my name' name would be pointed to from my)
  - int count -- the amount of times the connected word follows the first word
  - edge() -- parameterized constructor for edge struct
 */
struct edge {
  vertex* v;
  int count;
  edge(vertex* _v, int _count) : v(_v), count(_count) {}
};

/*
The vertex struct is used to store each unique word in the given input and all
the words that have followed it.
Properties:
  - std::string word -- this is the actual word the defines the vertex
  - std::vector<edge> edges -- this vector holds all the vertices of words that
                               could follow the current vertex
  - vertex() -- parameterized constructor for vertex struct
 */
struct vertex {
  std::string word;
  std::vector<edge> edges;
  vertex(std::string _word) : word(_word) {}
};

/*
  Generator Class
  Purpose: This class is used to create a graph of words from an input. This
           graph will keep track of each unique word and created edges between
           words that follow each other.
  Note: The graph will contain a START vertex and END vertex. All words that
        could start sentences will be pointed to from the START. All words that
        could end sentences will point to END. Traversal for sentence creation
        will traverse from START until END.
 */
class Generator {
 public:
  /*
  Method: addEdge
  Return Type: void
  Purpose: This method is used to create an edge between two vertices.
  Parameters:
    - Param1 - std::string -- the word of the vertex to create the edge from
    - Param2 - std::string -- the word of the vertex to create the edge to
   */
  void addEdge(std::string, std::string);

  /*
  Method: addVertex
  Return Type: void
  Purpose: This method is used to created new vertices and add them to the
           vertices vector.
  Parameters:
    - Param1 - std::string -- the word value of the vertex being created
   */
  void addVertex(std::string);

  /*
  Method: generateSentence
  Return Type: std::string
  Parameters:
    -none
  Expected Return:
    - sentence generated from traversing through the graph from START to END
   */
  std::string generateSentence();

 private:
  /*
  This vector will hold all vertices in the graph
   */
  std::vector<vertex> vertices;

  /*
  Method: findVertex
  Return Type: vertex*
  Purpose: This method will check through the vector of vertices and see if
           there is a vertex with the given word.
  Parameters:
    - Param1 - std::string -- the word of the vertex being located
  Expected Return:
    - pointer to the vertex of given word if found
    - nullptr if vertex is not found
   */
  vertex* findVertex(std::string);

  /*
  Method: findEdge
  Return Type: edge*
  Purpose: This method will check through the edges vector of word 1 to see if
           there is an edge to word 2.
  Parameters:
    - Param1 - std::string -- the first word in the edge
    - Param2 - std::string -- the second word in edge, the one being pointed to
  Expected Return:
    - pointer to edge between words given
    - nullptr if no edge is found
   */
  edge* findEdge(std::string, std::string);

  /*
  Method: isVertex
  Return Type: bool
  Purpose: This method will determine if a given word is already a vertex in the
           vertices vector.
  Parameters:
    - Param1 - std::string -- the word being checked if is a vertex
  Expected Return:
    - true if the word is a vertex stored in the vertices vector
    - false if the word is not a vertex in the vertices vector
   */
  bool isVertex(std::string);

  /*
  Method: isEdge
  Return Type: bool
  Purpose: This method will determine if there exists an edge between two words.
  Parameters:
    - Param1 - std::string -- the first word in the edge
    - Param2 - std::string -- the second word in the edge (one being pointed to)
  Expected Return:
    - true if edge exists between word one and word two
    - false if no edge exists between word one and word two
   */
  bool isEdge(std::string, std::string);
};

#endif