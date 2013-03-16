#include <gtk/gtk.h>
#include <iostream>
#include "Gui.h"
using namespace std;
int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        cout << "Usage: program savetimes.txt entrants.txt courses.txt nodes.txt\n";
    }
    else
    {
        for (int i = 0; i < argc;i++)
                cout << argv[i] << "\n";
        gtk_init(&argc, &argv);
        Gui g(argv[1],argv[2],argv[3],argv[4]);
        g.Load();
    }
    return 1;
} 

