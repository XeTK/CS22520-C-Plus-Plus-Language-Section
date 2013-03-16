#include <gtk/gtk.h>
#include <vector>
#include "Entrant.h"
#include "Course.h"
#include "Node.h"
#include "FileReader.h"
using namespace std;
class Gui
{
	public:
                Gui();
                void Load();
	protected:
		static void Submit(GtkWidget *widget, gpointer label);
		static void CB_Checked(GtkWidget *widget, gpointer window);
                static void combo_selected(GtkWidget *widget, gpointer window);
	
};
