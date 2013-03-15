/* 
 * File:   Entrant.h
 * Author: THR2
 *
 * Created on 14 March 2013, 16:15
 */

#include <string>
#include "Course.h"
using namespace std;

#ifndef ENTRANT_H
#define	ENTRANT_H

class Entrant 
{
    int competitor_number;
    Course course;
    string competitor_name;
    public:
        Entrant(int com_num, Course course,string com_name);
        int get_entrant_no();
        Course get_course();
        string get_name();
    private:

};

#endif	/* ENTRANT_H */

