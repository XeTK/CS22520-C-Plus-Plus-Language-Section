/* 
 * File:   Node.cpp
 * Author: THR2
 * 
 * Created on 14 March 2013, 16:24
 */

//Data Class for holding the data from nodes

#include "Node.h"
#include <string>
using namespace std;
Node::Node(int node, string nodetype) 
{
    this->node = node;
    this->nodetype = nodetype;
}
Node::Node(){}
Node::~Node(){}
int Node::get_node()
{
    return this->node;
}

string Node::get_nodetype()
{
    return this->nodetype;
}
