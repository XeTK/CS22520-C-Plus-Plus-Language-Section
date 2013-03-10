#include <gtk/gtk.h>
class Gui
{
	public:
		void Load();
		void Submit(GtkWidget *widget, gpointer label);
		void combo_selected(GtkWidget *widget, gpointer window);
	
};
