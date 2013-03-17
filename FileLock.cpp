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

using namespace std;
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
static vector<string> files;
bool FileLock::add_lock(string path)
{
    if (lock(path))
    {
        files.push_back(path);
        cout << "Locked File : " << path << endl;
        return true;
    }
    cout << "Failed to lock file : " << path << endl;
    return false;
}
bool FileLock::remove_locks()
{
    bool temp = true;
    for (int i = 0; i < files.size();i++)
    { 
        if (!unlock(files[i]))
        {
            temp = false;
            cout << "Failed to unlock File : " << files[i] << endl;
        }
        else
        {
            cout << "Unlocked File : " << files[i] << endl;
        }
    }
    return temp;
}
bool FileLock::lock(string path)
{
    return (fcntl(open(path.c_str(), O_RDWR), F_SETLK, file_lock(F_WRLCK,SEEK_SET)) == -1)?false:true;
}
bool FileLock::unlock(string path)
{
    return (fcntl(open(path.c_str(), O_RDWR), F_SETLKW, file_lock(F_UNLCK, SEEK_SET)) == -1)?false:true;
}
