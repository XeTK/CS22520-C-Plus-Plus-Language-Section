/* 
 * File:   Entrant.cpp
 * Author: THR2
 * 
 * Created on 14 March 2013, 16:15
 */

#include "Entrant.h"
#include "Course.h"
#include <string>

using namespace std;
Entrant::Entrant(int com_num, Course course,string com_name)
{
    this->competitor_number = com_num;
    this->course = course;
    this->competitor_name = com_name;
}
int Entrant::get_entrant_no()
{
    return this->competitor_number;
}
Course Entrant::get_course()
{
    return this->course;
}
string Entrant::get_name()
{
    return this->competitor_name;
}

