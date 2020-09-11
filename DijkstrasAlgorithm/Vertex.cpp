//---------------------------------------------------------------------------
// File: Vertex.cpp
// Author: Snehal Jogdand
// Date: 02/15/2020
// Program 3: Dijkstra's algorithm
//
// DESCRIPTION:
// Vertex: 
//  The class file for Vertex class
//  Provides the set of variables and functions to process a Vertex
//---------------------------------------------------------------------------

#include "Vertex.h"

//------------------------------------------------------------------------
// The default constructor that creates a new Vertex object 
// with the provided name
// @param name The vertex name 
Vertex::Vertex(string name) : name(name) {
}

//------------------------------------------------------------------------
// Overload output stream '<<' operator.
// @pre The vertex is a valid vertex object
// @post The vertex name is printed to the output stream
// @param output The output stream to print the output
// @param vertex The Vertex object to output
ostream& operator<<(ostream& output, const Vertex& vertex) {
   output << vertex.name;
   return output;
}

//------------------------------------------------------------------------
// The vertex object destructor 
// @pre none
// @post the vertex object is completely deleted
Vertex::~Vertex() {
}