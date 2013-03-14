/* 
 * File:   course.cpp
 * Author: THR2
 * 
 * Created on 14 March 2013, 16:16
 */

#include "Course.h"

Course::Course(char course_ident) 
{
    this->course = course_ident;
}
char Course::get_course()
{
    return this->course;
}
std::vector<Node> Course::get_nodes()
{
    return this->nodes;
}
void Course::add_node(Node in_node)
{
    this->nodes.push_back(in_node);
}


