#include <cstdlib>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "FileLock.h"

//Based of Neil Snook's file locking example

using namespace std;
//Struct holding the info about the type of lock that is going to be placed on a file
struct flock* file_lock(short type, short whence) 
{
    static struct flock ret;
    ret.l_type = type;
    ret.l_start = 0;
    ret.l_whence = whence;
    ret.l_len = 0;
    ret.l_pid = getpid();
    return &ret;
}
//create a static store of the files that we are going to lock
static vector<string> files;
//Pass in the path of the file we are going to lock then return a boolean to say it was successfully locked
bool FileLock::add_lock(string path)
{
    //lock the file 
    if (lock(path))
    {
        //if the file was successfully locked then we add it to the list of files that were locked
        files.push_back(path);
        //print out the path and say that file has been locked
        cout << "Locked File : " << path << endl;
        return true;
    }
    //if it hasn't then we return a error to say the file has not been locked
    cout << "Failed to lock file : " << path << endl;
    return false;
}
//Method to remove all locks on the files that have been locked previously
bool FileLock::remove_locks()
{
    //create a boolean flag so we know if any of the files have failed to be unlocked
    bool temp = true;
    //loop through all the files that are stored in the vector
    for (int i = 0; i < files.size();i++)
    { 
        //try to unlock the file
        if (!unlock(files[i]))
        {
            //if it fails then we set the global boolean to false so we know one has failed
            temp = false;
            //print out that we have failed to unlock the file
            cout << "Failed to unlock File : " << files[i] << endl;
        }
        else
        {
            //else say we have unlocked the file successfully
            cout << "Unlocked File : " << files[i] << endl;
        }
    }
    return temp;
}
//Simple method to lock files based on Neil Snook's example
bool FileLock::lock(string path)
{
    //it returns a true or fault value to show a file has been locked or unlocked
    return (fcntl(open(path.c_str(), O_RDWR), F_SETLK, file_lock(F_WRLCK,SEEK_SET)) == -1)?false:true;
}
bool FileLock::unlock(string path)
{
    return (fcntl(open(path.c_str(), O_RDWR), F_SETLKW, file_lock(F_UNLCK, SEEK_SET)) == -1)?false:true;
}
