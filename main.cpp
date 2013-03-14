#include <gtk/gtk.h>
#include "Gui.h"
using namespace std;
int main(int argc, char* argv[])
{
        printf("%s",argv[1]);
        gtk_init(&argc, &argv);
	Gui g;
	g.Load();
	return 0;
} 

