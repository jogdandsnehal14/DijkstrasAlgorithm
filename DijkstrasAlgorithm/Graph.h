//---------------------------------------------------------------------------
// File: Graph.h
// Author: Snehal Jogdand
// Date: 02/15/2020
// Program 3: Dijkstra's algorithm
//
// DESCRIPTION:
// Graph: 
//  The header file for Graph class
//  Provides the set of variables and functions to process a Graph
//---------------------------------------------------------------------------

#ifndef GRAPH_
#define GRAPH_

#include "Vertex.h"
#include <iostream>
#include <fstream>

using namespace std;

class Graph {
public:
   //------------------------------------------------------------------------
   // The default constructor that creates a new Graph object 
   // @pre none
   // @post creates a Graph object with size 0
   Graph();

   //------------------------------------------------------------------------
   // The copy constructor that deep copies the provided Graph object
   // @pre graph should be a valid Graph object
   // @post creates a deep copy of give Graph object
   // @param graph The graph to be copied
   Graph(const Graph& graph);

   //------------------------------------------------------------------------
   // The overloaded assignment operator to deep copy the provided Graph object
   // @pre rhs should be a valid Graph object
   // @post creates a deep copy of give Graph object
   // @param rhs The graph to be copied
   Graph operator=(const Graph& rhs);

   //------------------------------------------------------------------------
   // Builds the graph from the provided input file stream in inFile
   // @pre infile correctly formatted input file stream
   // @post builds the graph object
   // @param infile The file input stream object
   void buildGraph(ifstream& infile);

   //------------------------------------------------------------------------
   // Inserts an edge from source to destination vertex with given weight
   // @pre source and destination are valid vertex values
   // @post creates a new edge from source to destination vertex
   // @param source The source vertex
   // @param destination The destination vertex
   // @param weight The weight of the edge
   void insertEdge(int source, int destination, int weight);

   //------------------------------------------------------------------------
   // Removes an edge from source to destination vertex
   // @pre source and destination are valid vertex values
   // @post removes the edge from source to destination vertex
   // @param source The source vertex
   // @param destination The destination vertex
   void removeEdge(int source, int destination);

   //------------------------------------------------------------------------
   // Builds the table with shortest path
   // @pre the graph is already being built from the input file
   // @post builds the table with shortest path between vertices
   void findShortestPath();

   //------------------------------------------------------------------------
   // Displays a formatted details of shortest path for all vertices
   // @pre none
   // @post displays the formatted shortest paths details
   void displayAll();

   //------------------------------------------------------------------------
   // Displays the shortest path details from source to destinaion vertex
   // @pre none
   // @post displays the shortest path from source to destination with details
   // @param source The source vertex
   // @param destination The destination vertex
   void display(int source, int destination);

   //------------------------------------------------------------------------
   // The Graph object destructor 
   // @pre none
   // @post the graph object is completely deleted 
   //    with corresponding memory deallocated
   ~Graph();

private:
   static const int INFINITE = INT_MAX;
   static const int MAX_VERTICES = 101;

   // The edge node structure
   struct EdgeNode {       // can change to a class, if desired
      int adjVertex;       // subscript of the adjacent vertex 
      int weight;          // weight of edge
      EdgeNode* nextEdge;

      //------------------------------------------------------------------------
      // The default constructor that creates a new EdgeNode object 
      // @pre none
      // @post creates a EdgeNode object with 0 weight and no edges
      EdgeNode();

      //------------------------------------------------------------------------
      // The constructor that creates a new EdgeNode object 
      // @pre none
      // @post creates a EdgeNode object with given weight and the vertex
      // @param weight The weight of the edge
      // @param adjVertex The adjacent vertex for the edge
      EdgeNode(int weight, int adjVertex);
   };

   struct VertexNode {
      EdgeNode* edgeHead;    // head of the list of edges
      Vertex* data;          // store vertex data here

      //------------------------------------------------------------------------
      // The default constructor that creates a new VertexNode object 
      // @pre none
      // @post creates a VertexNode object with no data and no edges
      VertexNode();

      //------------------------------------------------------------------------
      // The constructor that creates a new VertexNode object 
      // @pre none
      // @post creates a VertexNode object with given vertex
      // @param vertex The vertex object
      VertexNode(Vertex* vertex);
   };

   // array of VertexNodes
   VertexNode vertices[MAX_VERTICES];

   // table of information for Dijkstra's algorithm
   struct Table {
      bool visited;   // whether vertex has been visited
      int dist;       // shortest known distance from source
      int path;       // previous vertex in path of min dist
   };

   int size;          // number of vertices in the graph
   Table T[MAX_VERTICES][MAX_VERTICES];
   // stores visited, distance, path -
   // two dimensional in order to solve
   // for all sources

   //------------------------------------------------------------------------
   // Finds the next unvisited vertex with lowest weight
   // @pre none
   // @post returns the next unvisited vertex with lowest weight
   // @param source The source vertex
   // @param destination The destination vertex
   // @returns the next unvisited vertex with lowest weight
   int getLowestWeightUnvisited(int source) const;

   //------------------------------------------------------------------------
   // Recomputes the path and weights for the given source and destination vertex
   // @pre source and destination are valid vertex values
   // @post The new shortest path is computed with weights
   // @param source The source vertex
   // @param destination The destination vertex
   void recomputeWeight(int source, int destination);

   //------------------------------------------------------------------------
   // Displays the shortest path from source to destinaion vertex
   // @pre source and destination are valid vertex values
   // @post displays the shortest path from source to destination
   // @param source The source vertex
   // @param destination The destination vertex
   void displayRecursive(int source, int destination) const;

   //------------------------------------------------------------------------
   // Displays the shortest path vertex names from source to destinaion vertex
   // @pre source and destination are valid vertex values
   // @post displays the shortest path vertex names from source to destination
   // @param source The source vertex
   // @param destination The destination vertex
   void displayPathNamesRecursive(int source, int destination) const;

   //------------------------------------------------------------------------
   // Deletes all the data from the Graph and deallocates the assigned memory
   // @pre none
   // @post all Graph data is deleted and memory freed
   void deleteGraph();
};
#endif