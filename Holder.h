/* 
 * File:   Holder.h
 * Author: THR2
 *
 * Created on 14 March 2013, 18:49
 */

#include <vector>
#include "Entrant.h"
#include "Course.h"
using namespace std;

#ifndef HOLDER_H
#define	HOLDER_H
class Holder 
{
    vector<Entrant> entrants;
    vector<Course> courses;
    
    public:
        vector<Entrant> get_entrants();
        vector<Course> get_courses();
        void add_course(Course in_course);
        void add_entrant(Entrant in_entrant);
    private:


};

#endif	/* HOLDER_H */

