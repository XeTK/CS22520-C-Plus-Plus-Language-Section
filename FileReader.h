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
            ~FileReader();
            vector<Entrant> get_entrants(string entrant_path,string course_path,string node_path);
        private:
            vector<string> get_file_contents(string path);
            vector<Node> get_nodes(string path);
            vector<Course> get_courses(string course_path,string node_path);
            
};

#endif	/* FILEREADER_H */

