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
#include <stdio.h>
#include <stdlib.h>
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
        if (temp.empty()||temp == "")
            break;
        temp_strings.push_back(temp);
    }
    infile.close();
    return temp_strings;
}
vector<Course> FileReader::get_courses(string path)
{
    vector<Course> temp_c;
    vector<string> temp_l = get_file_contents(path);
    vector<Node> temp_n = get_nodes("Data/nodes.txt");
    for (int i = 0; i < temp_l.size();i++)
    {
        char ident;
        sscanf(temp_l[i].c_str(),"%c",&ident);
        Course t_course(ident);
        string buf = "";
        temp_l[i] += " ";
        int loc = 0;
        for (int j = 0;j < temp_l[i].size();j++)
        {
            if (temp_l[i][j] == ' ')
            {
                if (loc > 1)
                {
                    int node = atoi(buf.c_str());
                    for (int k = 0; k < temp_n.size();k++)
                    {
                        if (temp_n[k].get_node() == node)
                        {
                            t_course.add_node(temp_n[k]);
                        }
                    }
                }
                loc++;
                buf = "";
            }
            else
            {
                buf += temp_l[i][j];
            }

        }
        cout << "\n";
    }
        
}
vector<Entrant> FileReader::get_entrants(string path)
{

}
vector<Node> FileReader::get_nodes(string path)
{
    vector<Node> temp_n;
    vector<string> temp_l = get_file_contents(path);
    for (int i = 0;i < temp_l.size();i++)
    {
        int n;
        char *b;
        sscanf(temp_l[i].c_str(),"%d %s",&n, b);
        Node t_n(n,b);
        temp_n.push_back(t_n);
    }
    return temp_n;
}
            
