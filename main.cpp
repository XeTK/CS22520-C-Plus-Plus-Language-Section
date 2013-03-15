#include <gtk/gtk.h>
#include "Gui.h"
#include "FileReader.h"
using namespace std;
int main(int argc, char* argv[])
{
    /*gtk_init(&argc, &argv);
    Gui g;
    g.Load();*/
    FileReader fr;
    fr.get_courses("Data/courses.txt");
    return 1;
} 

