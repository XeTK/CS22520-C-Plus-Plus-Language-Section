#include <gtk/gtk.h>
#include "Gui.h"

int main(int argc, char** argv)
{
	gtk_init(&argc, &argv);
	Gui g;
	g.Load();
	return 0;
} 

