#include <gtk/gtk.h>
#include <iostream>
#include "Gui.h"
#include "FileLock.h"
using namespace std;
int main(int argc, char* argv[])
{
    FileLock fl;
    if (argc < 4)
    {
        cout << "Usage: program savetimes.txt entrants.txt courses.txt nodes.txt\n";
    }
    else
    {
        for (int i = 0; i < argc;i++)
                cout << argv[i] << "\n";
        gtk_init(&argc, &argv);
        for (int i = 1; i <= 4;i++)
                fl.add_lock(argv[i]);
        Gui g(argv[1],argv[2],argv[3],argv[4]);
        g.Load();
    }
    fl.remove_locks();
    return 1;
} 

