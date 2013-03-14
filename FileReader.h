/* 
 * File:   FileReader.h
 * Author: THR2
 *
 * Created on 14 March 2013, 19:39
 */
#include <vector>
#include <string>
#include "Course.h"
#include "Entrant.h"
using namespace std;
#ifndef FILEREADER_H
#define	FILEREADER_H

class FileReader
{
        public:
            vector<Course> get_courses(string path);
            vector<Entrant> get_entrants(string path);
        private:
            vector<string> get_file_contents(string path);
            
};

#endif	/* FILEREADER_H */

