/* 
 * File:   course.cpp
 * Author: THR2
 * 
 * Created on 14 March 2013, 16:16
 */
//Data class to hold all the info from a course object along with all the nodes that are attached to it
#include "Course.h"
using namespace std;
Course::Course(){}

Course::Course(char course_ident) 
{
    this->course = course_ident;
}
Course::~Course(){}
char Course::get_course()
{
    return this->course;
}
vector<Node> Course::get_nodes()
{
    return this->nodes;
}
void Course::add_node(Node in_node)
{
    this->nodes.push_back(in_node);
}


