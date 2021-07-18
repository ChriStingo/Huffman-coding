#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector> 
#include <fstream> 
#include <string>         


using namespace std; 

namespace tree {

    typedef int Label;
    typedef string Weight;

    struct vertexNode; // defined in Tree.cpp

    typedef vertexNode* Tree; // first vertex is the first element of tree

    const Tree emptyTree = NULL; 

    // return empty tree
    Tree createEmptyTree();

    // add new vertex with label, fail if already in
    bool addVertex(Label, Tree&);

    // add new edge between vertex with weight = Weight
    // fail if edge already in or there aren't both vertex
    bool addEdge(Label, Label, Weight, Tree&);

    // true if it's empty
    bool isEmpty(const Tree&);

    void printTree(const tree::Tree&);

    // DFS
    string dfs(tree::Tree&, Label);
}
