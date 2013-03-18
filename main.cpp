#include <gtk/gtk.h>
#include <iostream>
#include "Gui.h"
#include "FileLock.h"
using namespace std;
//This is the main method of the program this is where it is executed
int main(int argc, char* argv[])
{
    //Declare the file lock class just incase we need to lock files
    FileLock fl;
    //Check if the arguments are there to continue, we should have 4 as we have 4 files we need to continue
    if (argc < 4)
    {
        //If we havent got 4 files then we print out the usage info for the end user to follow
        cout << "Usage: program savetimes.txt entrants.txt courses.txt nodes.txt\n";
    }
    else
    {
        //we print out the files paths for the files that we have, this is debugging 
        for (int i = 0; i < argc;i++)
                cout << argv[i] << "\n";
        //Start up the gtk core to show are gui
        gtk_init(&argc, &argv);
        //lock the files that we will be working on
        for (int i = 1; i <= 4;i++)
                fl.add_lock(argv[i]);
        //pass in the file paths to the gui that is going to be created
        Gui g(argv[1],argv[2],argv[3],argv[4]);
        //load the gui for the end user to see
        g.Load();
    }
    //when the program exits we remove the file locks from all the files that we have locked
    fl.remove_locks();
    //exit the program
    return 1;
} 

