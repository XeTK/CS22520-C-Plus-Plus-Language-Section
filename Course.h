/* 
 * File:   course.h
 * Author: THR2
 *
 * Created on 14 March 2013, 16:16
 */
#include <vector>
#include "Node.h"
using namespace std;
#ifndef COURSE_H
#define	COURSE_H

class Course 
{
    char course;
    vector<Node> nodes;
    public:
        Course(char course_ident);
        Course();
        ~Course();
        char get_course();
        vector<Node> get_nodes();
        void add_node(Node in_node);
};

#endif	/* COURSE_H */

