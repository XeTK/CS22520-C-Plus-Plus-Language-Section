/* 
 * File:   FileReader.cpp
 * Author: THR2
 * 
 * Created on 14 March 2013, 16:15
 */
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "FileReader.h"
using namespace std;
//Destructor for clearing things when we are done
FileReader::~FileReader(){}
//This method reads the whole file into a vector for use to use
vector<string> FileReader::get_file_contents(string path)
{
    //declare are temp vector to hold are file before we manipulate it
    vector<string> temp_strings;
    //have a temp string to hold are string before it is added to the vector
    string temp;
    //open are file in a stream for us to work on
    ifstream infile(path.c_str());
    //if we havent reached the end of the file we loop through
    while(!infile.eof())
    {
        //get a line from the file and put it into the temp string we have
        getline(infile,temp);
        //if the string is empty or useless to us then we break the reading of the file
        if (temp.empty()||temp == "")
            break;
        //and if it is good to use then we add it to the vector list for later
        temp_strings.push_back(temp);
    }
    //close the file so that others can access it if need be
    infile.close();
    //return the vector containing all the strings we have read from the file
    return temp_strings;
}
//Method to add a line to the end of a file
void FileReader::add_to_file(string path, string line)
{
    //read the current file into a vector
    vector<string> cur_file = get_file_contents(path);
    //add a new line to the end of the vector
    cur_file.push_back(line);
    //open the file in a stream
    ofstream file(path.c_str());
    //if the file is open to write to, loop through the array of vectors and add the value to the file till we reach the end of the file
    if (file.is_open())
        for (int i = 0; i < cur_file.size();i++)
            file << cur_file[i] << "\n";
    //close the file we are writing to so other things can access it
    file.close();
}
//method to dynamicly parse the courses file
vector<Course> FileReader::get_courses(string course_path,string node_path)
{
    //keep a vector for holding the courses
    vector<Course> temp_c;
    //get the list of courses from the file
    vector<string> temp_l = get_file_contents(course_path);
    //get the nodes from the node file as we can add them to the courses
    vector<Node> temp_n = get_nodes(node_path);
    for (int i = 0; i < temp_l.size();i++)
    {
        //get the course identifier
        char ident;
        sscanf(temp_l[i].c_str(),"%c",&ident);
        //add it to are new course
        Course t_course(ident);
        //create a buffer for are char's
        string buf = "";
        //the line has a space added to the end so we dont miss the last node, dirty but does the job
        temp_l[i] += " ";
        //keep the location we are in the string
        int loc = 0;
        //go through the char array that is the string for the courses
        for (int j = 0;j < temp_l[i].size();j++)
        {
            //if the char we are looking at is a space then we know that we are between nodes
            if (temp_l[i][j] == ' ')
            {
                //if we are past the number of nodes and course identifier
                if (loc > 1)
                {
                    //convert are buffer into the node number
                    int node = atoi(buf.c_str());
                    //loop through nodes that we have to find it
                    for (int k = 0; k < temp_n.size();k++)
                    {
                        //if the node in the vector = the node for the course
                        if (temp_n[k].get_node() == node)
                        {
                            //add it to the course so we can refrence back to it
                            t_course.add_node(temp_n[k]);
                            //we have done the work so breaking from loop
                            break;
                        }
                    }
                }
                //increment are location through the char array
                loc++;
                //clear are buffer
                buf = "";
            }
            else
            {
                //add the char to the string
                buf += temp_l[i][j];
            }

        }
        //add the course to the vector of courses
        temp_c.push_back(t_course);
    }
    //return the list of courses to the previous method
    return temp_c;
        
}
//read in the entrants from the file
vector<Entrant> FileReader::get_entrants(string entrant_path,string course_path,string node_path)
{
    //keep a vector holding the entrants for later use
    vector<Entrant> temp_e;
    //get the contents of the entrants file
    vector<string> temp_l = get_file_contents(entrant_path);
    //get the courses from the files for use with tieing the entrants in with them
    vector<Course> temp_c = get_courses(course_path,node_path);
    //loop through the entrants file
    for (int i = 0; i < temp_l.size();i++)
    {
        //keep the entrant number
        int e_no;
        //keep the course
        char e_co;
        //keep there name
        char *e_na;
        //allocate some memory to the users name 
        e_na = (char*)malloc(sizeof(char*) * 80);
        //parse the line getting the relivant information
        sscanf(temp_l[i].c_str(),"%d %c %[^\t\n]",&e_no,&e_co, e_na);
        //loop through courses
        for (int j = 0; j < temp_c.size();j++)
        {
            //if the course identifier is the same as the entrants
            if (temp_c[j].get_course() == e_co)
            {
                //we add the course object for the entrant to make tracking thins easier
                Entrant t_e(e_no,temp_c[j],e_na);
                //we add the entrant to the list of entrants
                temp_e.push_back(t_e);
                //break from the loop as we have done what we wanted todo
                break;
            }
        }
    }
    //return the list of entrants to the previous method
    return temp_e;
}
//read in the nodes from the nodes.txt file
vector<Node> FileReader::get_nodes(string path)
{
    //declare a temp vector of nodes
    vector<Node> temp_n;
    //get the file contents of the nodes file to be manipulated
    vector<string> temp_l = get_file_contents(path);
    //loop through the nodes file
    for (int i = 0;i < temp_l.size();i++)
    {
        //temp int for the node number
        int n;
        //store for the string for the node type
        char *b;
        //allocate some memory to the string otherwise we segfault
        b = (char*)malloc(sizeof(char*) * 2);
        //now we parse the line we are working on
        sscanf(temp_l[i].c_str(),"%d %s",&n, b);
        //create a new node with theses values
        Node t_n(n,b);
        //add them to are vector list
        temp_n.push_back(t_n);
    }
    //return the nodes
    return temp_n;
}
            
