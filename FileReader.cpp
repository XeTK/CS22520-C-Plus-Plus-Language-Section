/* 
 * File:   Entrant.cpp
 * Author: THR2
 * 
 * Created on 14 March 2013, 16:15
 */
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "FileReader.h"
using namespace std;
vector<string> FileReader::get_file_contents(string path)
{
    vector<string> temp_strings;
    string temp;
    ifstream infile(path.c_str());
    while(!infile.eof())
    {
        getline(infile,temp);
        temp_strings.push_back(temp);
    }
    infile.close();
    return temp_strings;
}
vector<Course> FileReader::get_courses(string path)
{
    get_file_contents(path);
}
vector<Entrant> FileReader::get_entrants(string path)
{

}
            
