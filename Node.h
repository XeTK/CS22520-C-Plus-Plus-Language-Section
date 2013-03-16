/* 
 * File:   Node.h
 * Author: THR2
 *
 * Created on 14 March 2013, 16:24
 */
using namespace std;

#ifndef NODE_H
#define	NODE_H
#include <string>
class Node 
{
    int node;
    string nodetype;
    public:
        Node(int node, string nodetype);
        Node();
        ~Node();
        int get_node();
        string get_nodetype();

};

#endif	/* NODE_H */

