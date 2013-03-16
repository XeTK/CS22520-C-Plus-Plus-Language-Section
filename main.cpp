#include <gtk/gtk.h>
#include "Gui.h"
using namespace std;
int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);
    Gui g;
    g.Load();
    return 1;
} 

