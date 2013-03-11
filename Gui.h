#include <gtk/gtk.h>
class Gui
{
	public:
		void Load();
	protected:
		static void Submit(GtkWidget *widget, gpointer label);
		static void combo_selected(GtkWidget *widget, gpointer window);
	
};
