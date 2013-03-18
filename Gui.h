#include <gtk/gtk.h>
#include <vector>
#include "Entrant.h"
#include "Course.h"
#include "Node.h"
#include "FileReader.h"
using namespace std;
//Function prototypes for the gui class
class Gui
{
	public:
                Gui(string save_path, string entrant_path, string course_path, string node_path);
                void Load();
        //methods must be protected and static as gtk is a c libary and without them being static and private nothing works
	protected:
		static void Submit(GtkWidget *widget, gpointer label);
		static void CB_Checked(GtkWidget *widget, gpointer window);
                static void combo_selected(GtkWidget *widget, gpointer window);
                static void message_box(GtkWidget* parent, const char* title, const char* message);
                static void node_combo_selected(GtkWidget *widget, gpointer window);
	
};
