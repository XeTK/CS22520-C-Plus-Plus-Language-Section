/* 
 * File:   Holder.cpp
 * Author: THR2
 * 
 * Created on 14 March 2013, 18:49
 */

#include "Holder.h"
using namespace std;
vector<Entrant> Holder::get_entrants()
{
    return this->entrants;
}
vector<Course> Holder::get_courses()
{
    return this->courses;
}
void Holder::add_course(Course in_course)
{
    this->courses.push_back(in_course);
}
void Holder::add_entrant(Entrant in_entrant)
{
    this->entrants.push_back(in_entrant);
}


