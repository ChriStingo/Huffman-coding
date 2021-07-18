#include "Tree.h"

using namespace tree;

/*******************************************************************************************************/
// Struct
/*******************************************************************************************************/

// half edge
struct halfEdgeNode {
  vertexNode *vertPtr;
  Weight weight;
  halfEdgeNode* next; // next vertex
};

struct tree::vertexNode {
    Label label;    
    halfEdgeNode *adjList;
    vertexNode *next;
    bool visited;      // for DFS
};

/*******************************************************************************************************/
// Const
/*******************************************************************************************************/

halfEdgeNode* const emptyHalfEdgeNode = NULL;

/*******************************************************************************************************/
// Aux function
/*******************************************************************************************************/

// return vertex with label l
vertexNode* getVertex(Label l, const Tree& g) {
  for (tree::Tree v = g; v != emptyTree; v = v->next) {
   if (v->label == l) return  v;
  }
  return emptyTree;
}

// return true if vertex in tree
bool isVertexInTree(Label l, const Tree& g) {
  return (getVertex(l, g)!=emptyTree);
}



// true if edge is in tree
bool isEdgeInTree(Label from, Label to, const Tree& g) {
 vertexNode* vNode = getVertex(from, g);
 if (vNode == emptyTree) return false;
 for (halfEdgeNode* n = vNode->adjList; n != emptyHalfEdgeNode; n = n->next) {
    if (n->vertPtr->label == to ) return true;
  }
 return false;
}

// add half edge if both vertex are in the tree
void addHalfEdge(Label from, Label to, Weight w, Tree& g) {
  halfEdgeNode *e = new halfEdgeNode;
  e->vertPtr = getVertex(to, g);
  e->weight = w;
  
  vertexNode* vNode = getVertex(from, g);

  if (vNode->adjList == emptyHalfEdgeNode) {
    vNode->adjList = e;
    e->next = emptyHalfEdgeNode;
  } else {
    e->next = vNode->adjList;
    vNode->adjList = e;
  }
}

// print adj list
void printAdjList(Label l, const Tree& g) {
 vertexNode* vNode = getVertex(l, g);
 if (vNode==emptyTree) return;
 for (halfEdgeNode* n = vNode->adjList; n != emptyHalfEdgeNode; n = n->next) {
    cout << "(" << n->vertPtr->label << ", " << n->weight << ")" << " ";
  }
 cout << endl; 
}


/*******************************************************************************************************/
// tree
/*******************************************************************************************************/

Tree tree::createEmptyTree()
{
  return emptyTree;
}

// add new vertex with label, fail if already in
bool tree::addVertex(Label l, Tree& g) {
  if (isVertexInTree(l, g))
    return false;  // already in

  Tree v = new vertexNode;
  v->label = l;
  v->adjList = emptyHalfEdgeNode;
  v->visited = false;
  if (isEmpty(g)) {
    g = v;
    v->next = emptyTree;
  } else {
    v->next = g;
    g = v;
  }
  return true;
}

// add new edge between vertex with weight = Weight
// fail if edge already in or there aren't both vertex
bool tree::addEdge(Label from, Label to, Weight w, Tree& g) {
  // no loop
  if (from == to)
    return false;

  if (!isVertexInTree(from, g) || !isVertexInTree(to, g))
    return false;

  if (isEdgeInTree(from,to,g) || isEdgeInTree(to,from,g))
    return false;

  addHalfEdge(from, to, w, g);
  return true;
}

// true if it's empty
bool tree::isEmpty(const Tree& g)
{ 
   return (g==emptyTree);
}

// compute the DFS
string tree::dfs(Tree& g, Label l){
  if(g == emptyTree)
    return "N";
  if(g->label == l)
    return "";
  if(g->adjList == emptyHalfEdgeNode)
    return "N";
  string left = dfs(g->adjList->vertPtr, l);
  string right = dfs(g->adjList->next->vertPtr, l);
  if(left[left.length()-1] == 'N')
    return g->adjList->next->weight + right;
  else
    return g->adjList->weight + left;
}

/*******************************************************************************************************/
void tree::printTree(const tree::Tree& g) {
  for (tree::Tree v = g; v != emptyTree; v = v->next) {
    cout << v->label << ": ";
    printAdjList(v->label, g);
  }
}
