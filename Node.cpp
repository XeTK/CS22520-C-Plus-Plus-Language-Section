/* 
 * File:   Node.cpp
 * Author: THR2
 * 
 * Created on 14 March 2013, 16:24
 */

#include "Node.h"
using namespace std;
Node::Node(int node, char *nodetype) 
{
    this->node = node;
    this->nodetype = nodetype;
}
int Node::get_node()
{
    return this->node;
}

char *Node::get_nodetype()
{
    return this->nodetype;
}
