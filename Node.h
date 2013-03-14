/* 
 * File:   Node.h
 * Author: THR2
 *
 * Created on 14 March 2013, 16:24
 */

#ifndef NODE_H
#define	NODE_H

class Node 
{
    int node;
    char *nodetype;
    public:
        Node(int node, char *nodetype);
        int get_node();
        char *get_nodetype();

};

#endif	/* NODE_H */

