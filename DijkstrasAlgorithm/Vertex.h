//---------------------------------------------------------------------------
// File: Vertex.h
// Author: Snehal Jogdand
// Date: 02/15/2020
// Program 3: Dijkstra's algorithm
//
// DESCRIPTION:
// Vertex: 
//  The header file for Vertex class
//  Provides the set of variables and functions to process a Vertex
//---------------------------------------------------------------------------

#ifndef VERTEX_
#define VERTEX_

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

//---------------------------------------------------------------------------
// Vertex: The header file for Vertex class
//  Provides the set of variables and functions to process a Vertex
//---------------------------------------------------------------------------
class Vertex {
private:
   string name; // The name of the vertex

public:
   //------------------------------------------------------------------------
   // The default constructor that creates a new Vertex object 
   // with the provided name
   // @param name The vertex name 
   Vertex(string name);

   //------------------------------------------------------------------------
   // Overload output stream '<<' operator.
   // @pre The vertex is a valid vertex object
   // @post The vertex name is printed to the output stream
   // @param output The output stream to print the output
   // @param vertex The Vertex object to output
   friend ostream& operator<<(ostream& output, const Vertex& vertex);

   //------------------------------------------------------------------------
   // The vertex object destructor 
   // @pre none
   // @post the vertex object is completely deleted
   ~Vertex();
}; // end Vertex
#endif