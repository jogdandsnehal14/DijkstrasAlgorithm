//---------------------------------------------------------------------------
// File: Graph.cpp
// Author: Snehal Jogdand
// Date: 02/15/2020
// Program 3: Dijkstra's algorithm
//
// DESCRIPTION:
// Vertex: 
//  The class file for Graph class
//  Provides the set of variables and functions to process a Graph
//---------------------------------------------------------------------------

#include <fstream>
#include "Graph.h"
#include <iomanip>

using namespace std;

//------------------------------------------------------------------------
// The default constructor that creates a new EdgeNode object 
// @pre none
// @post creates a EdgeNode object with 0 weight and no edges
Graph::EdgeNode::EdgeNode() : adjVertex(-1), weight(-1), nextEdge(nullptr) {
}

//------------------------------------------------------------------------
// The constructor that creates a new EdgeNode object 
// @pre none
// @post creates a EdgeNode object with given weight and the vertex
// @param weight The weight of the edge
// @param adjVertex The adjacent vertex for the edge
Graph::EdgeNode::EdgeNode(int weight, int adjVertex) {
   this->weight = weight;
   this->adjVertex = adjVertex;
   this->nextEdge = nullptr;
}

//------------------------------------------------------------------------
// The default constructor that creates a new VertexNode object 
// @pre none
// @post creates a VertexNode object with no data and no edges
Graph::VertexNode::VertexNode() : edgeHead(nullptr), data(nullptr) {
}

//------------------------------------------------------------------------
// The constructor that creates a new VertexNode object 
// @pre none
// @post creates a VertexNode object with given vertex
// @param vertex The vertex object
Graph::VertexNode::VertexNode(Vertex* vertex) : edgeHead(nullptr), data(vertex) {
}

//------------------------------------------------------------------------
// The default constructor that creates a new Graph object 
// @pre none
// @post creates a Graph object with size 0
Graph::Graph() : size(0) {
}

//------------------------------------------------------------------------
// The copy constructor that deep copies the provided Graph object
// @pre graph should be a valid Graph object
// @post creates a deep copy of give Graph object
// @param graph The graph to be copied
Graph::Graph(const Graph& graph) {
   deleteGraph();

   if (graph.size == 0) return;

   for (int i = 0; i < MAX_VERTICES; i++) {
      for (int j = 0; j < MAX_VERTICES; j++) {
         T[i][j].visited = false;
         T[i][j].path = INFINITE;
         T[i][j].dist = INFINITE;
      }
   }

   size = graph.size;
   for (int i = 0; i < graph.size; i++) {
      Vertex* vertex = new Vertex(*graph.vertices[i].data);
      vertices[i] = VertexNode(vertex);

      EdgeNode* current1 = nullptr;
      EdgeNode* current2 = graph.vertices[i].edgeHead;

      // set head node
      if (current2 != nullptr) {
         current1 = new EdgeNode(current2->weight, current2->adjVertex);
         current2 = current2->nextEdge;
         vertices[i].edgeHead = current1;
      }

      // set subsequent list nodes
      while (current2 != nullptr) {
         current1->nextEdge = new EdgeNode(current2->weight, current2->adjVertex);
         current2 = current2->nextEdge;
         current1 = current1->nextEdge;
      }
   }

   for (int i = 0; i < graph.size; i++) {
      for (int j = 0; j < graph.size; j++) {
         T[i][j].visited = graph.T[i][j].visited;
         T[i][j].path = graph.T[i][j].path;
         T[i][j].dist = graph.T[i][j].dist;
      }
   }
}

//------------------------------------------------------------------------
// The overloaded assignment operator to deep copy the provided Graph object
// @pre rhs should be a valid Graph object
// @post creates a deep copy of give Graph object
// @param rhs The graph to be copied
Graph Graph::operator=(const Graph& rhs) {
   if (this == &rhs) {
      return *this;
   }

   Graph copy(rhs);
   swap(T, copy.T);
   swap(vertices, copy.vertices);
   size = copy.size;

   return *this;
}

//-------------------------------- buildGraph ---------------------------------
// Builds a graph by reading data from an ifstream
// Preconditions:  infile has been successfully opened and the file contains
//                 properly formated data (according to the program specs)
// Postconditions: One graph is read from infile and stored in the object
void Graph::buildGraph(ifstream& infile) {
   infile >> size;                          // data member stores array size
   if (infile.eof())
      return;
   infile.ignore();                         // throw away '\n' to go to next line

   // get descriptions of vertices
   for (int v = 0; v < size; v++) {
      string name;
      getline(infile, name, '\n');      // read descriptions (use of this method is not mandatory)

      Vertex* vertex = new Vertex(name);
      vertices[v] = VertexNode(vertex);
   }

   // fill cost edge array
   int src = 1, destination = 1, weight = 1;
   for (;;) {
      infile >> src >> destination >> weight;
      if (src == 0 || infile.eof())
         break;
      insertEdge(src, destination, weight);
   }
}

//------------------------------------------------------------------------
// Inserts an edge from source to destination vertex with given weight
// @pre source and destination are valid vertex values
// @post creates a new edge from source to destination vertex
// @param source The source vertex
// @param destination The destination vertex
// @param weight The weight of the edge
void Graph::insertEdge(int source, int destination, int weight) {
   if (source < 1 || source > size || destination < 1 || destination > size || weight < 0) return;

   EdgeNode* previous = nullptr;
   EdgeNode* current = vertices[source - 1].edgeHead;

   // inserting first edge
   if (current == nullptr) {
      vertices[source - 1].edgeHead = new EdgeNode(weight, destination - 1);
      return;
   }

   // inserting next edge
   while (current != nullptr) {
      // Replace any previous edge that existed between the two vertices
      if (current->adjVertex == destination - 1) {
         current->weight = weight;
         return;
      }

      previous = current;
      current = current->nextEdge;
   }

   previous->nextEdge = new EdgeNode(weight, destination - 1);
}

//------------------------------------------------------------------------
// Removes an edge from source to destination vertex
// @pre source and destination are valid vertex values
// @post removes the edge from source to destination vertex
// @param source The source vertex
// @param destination The destination vertex
void Graph::removeEdge(int source, int destination) {
   if (source < 1 || source > size || destination < 1 || destination >  size || vertices[source - 1].edgeHead == nullptr) {
      cout << "Error: Enter valid source or destination value" << endl;
      return;
   }

   // delete head edge
   EdgeNode* edgeHead = vertices[source - 1].edgeHead;
   if (edgeHead->adjVertex == destination - 1) {
      vertices[source - 1].edgeHead = edgeHead->nextEdge;

      // cleanup the edgeHead memory
      delete edgeHead;
      edgeHead = nullptr;
      return;
   }

   // delete one of the subsequent edge
   EdgeNode* previous = edgeHead;
   EdgeNode* current = previous->nextEdge;
   while (current != nullptr) {
      if (current->adjVertex == destination - 1) {
         previous->nextEdge = current->nextEdge;

         // cleanup the deleted edge memory
         delete current;
         current = nullptr;
         return;
      }

      current = previous->nextEdge;
   }
}

//------------------------------------------------------------------------
// Builds the table with shortest path
// @pre the graph is already being built from the input file
// @post builds the table with shortest path between vertices
void Graph::findShortestPath() {
   for (int i = 0; i < MAX_VERTICES; i++)
      for (int j = 0; j < MAX_VERTICES; j++) {
         T[i][j].visited = false;
         T[i][j].path = INFINITE;
         T[i][j].dist = INFINITE;
      }

   for (int i = 0; i < size; i++) {
      T[i][i].path = 0;
      T[i][i].dist = 0;
      T[i][i].visited = true;
      recomputeWeight(i, i);

      // find shortest path for all vertices
      for (int j = 0; j < size; j++) {
         int lowestMove = getLowestWeightUnvisited(i);
         if (lowestMove != INFINITE) {
            T[i][lowestMove].visited = true;
            recomputeWeight(i, lowestMove);
         }
      }
   }
}

//------------------------------------------------------------------------
// Finds the next unvisited vertex with lowest weight
// @pre none
// @post returns the next unvisited vertex with lowest weight
// @param source The source vertex
// @param destination The destination vertex
// @returns the next unvisited vertex with lowest weight
int Graph::getLowestWeightUnvisited(int source) const {
   int minVertex = INFINITE;
   int minWeight = INFINITE;
   for (int i = 0; i < size - 1; i++)
      if (!T[source][i].visited && T[source][i].dist < minWeight) {
         minVertex = i;
         minWeight = T[source][i].dist;
      }

   return minVertex;
}

//------------------------------------------------------------------------
// Recomputes the path and weights for the given source and destination vertex
// @pre source and destination are valid vertex values
// @post The new shortest path is computed with weights
// @param source The source vertex
// @param destination The destination vertex
void Graph::recomputeWeight(int source, int destination) {
   EdgeNode* current = vertices[destination].edgeHead;

   while (current != nullptr) {
      if (!T[source][current->adjVertex].visited) {
         if (T[source][current->adjVertex].path == INFINITE || T[source][current->adjVertex].dist > T[source][destination].dist + current->weight) {
            T[source][current->adjVertex].dist = T[source][destination].dist + current->weight;
            T[source][current->adjVertex].path = destination + 1;
         }
      }

      current = current->nextEdge;
   }
}

//------------------------------------------------------------------------
// Displays a formatted details of shortest path for all vertices
// @pre none
// @post displays the formatted shortest paths details
void Graph::displayAll() {
   cout << setw(20) << left << "Description"
      << setw(10) << left << "From"
      << setw(10) << left << "To"
      << setw(10) << left << "Dist"
      << setw(10) << left << "Path" << endl;

   for (int i = 0; i < size; i++) {
      cout << *vertices[i].data << endl;
      for (int j = 0; j < size; j++) {
         if (T[i][j].path != INFINITE && T[i][j].path != 0) {
            cout << setw(20) << left << ""
               << setw(10) << left << i + 1
               << setw(10) << left << j + 1
               << setw(10) << left << T[i][j].dist;

            displayRecursive(i, j);
            cout << j + 1;

            cout << endl;
         }
         else if (T[i][j].path == INFINITE) {
            cout << setw(20) << left << ""
               << setw(10) << left << i + 1
               << setw(10) << left << j + 1
               << setw(10) << left << "--" << endl;
         }
      }
   }
}

//------------------------------------------------------------------------
// Displays the shortest path details from source to destinaion vertex
// @pre none
// @post displays the shortest path from source to destination with details
// @param source The source vertex
// @param destination The destination vertex
void Graph::display(int source, int destination) {
   if (source < 1 || source > size || destination < 1 || destination > size) {
      cout << "Error: Enter valid source or destination value" << endl;
      return;
   }

   if (T[source - 1][destination - 1].dist == INFINITE) {
      cout << "Error: No path exist from " << source << " to " << destination << endl;
      return;
   }

   cout << source << '\t' << destination << '\t' << T[source - 1][destination - 1].dist << '\t';
   displayRecursive(source - 1, destination - 1);
   cout << destination << endl;
   displayPathNamesRecursive(source - 1, destination - 1);
}

//------------------------------------------------------------------------
// Displays the shortest path from source to destinaion vertex
// @pre source and destination are valid vertex values
// @post displays the shortest path from source to destination
// @param source The source vertex
// @param destination The destination vertex
void Graph::displayRecursive(int source, int destination) const {
   if (T[source][destination].path == 0) return;
   displayRecursive(source, T[source][destination].path - 1);
   cout << T[source][destination].path << " ";
}

//------------------------------------------------------------------------
// Displays the shortest path vertex names from source to destinaion vertex
// @pre source and destination are valid vertex values
// @post displays the shortest path vertex names from source to destination
// @param source The source vertex
// @param destination The destination vertex
void Graph::displayPathNamesRecursive(int source, int destination) const {
   if (T[source][destination].path == 0) {
      cout << *vertices[destination].data << endl;
   }
   else if (T[source][destination].path > 0) {
      displayPathNamesRecursive(source, T[source][destination].path - 1);
      cout << *vertices[destination].data << endl;
   }
}

//------------------------------------------------------------------------
// Deletes all the data from the Graph and deallocates the assigned memory
// @pre none
// @post all Graph data is deleted and memory freed
void Graph::deleteGraph() {
   for (int i = 0; i < size; i++) {
      EdgeNode* current = vertices[i].edgeHead;
      while (current != nullptr) {
         EdgeNode* toBeDeleted = current;
         current = current->nextEdge;
         delete toBeDeleted;
         toBeDeleted = nullptr;
      }

      delete vertices[i].data;
      vertices[i].data = nullptr;
   }
}

//------------------------------------------------------------------------
// The Graph object destructor 
// @pre none
// @post the graph object is completely deleted 
//    with corresponding memory deallocated
Graph::~Graph() {
   deleteGraph();
}