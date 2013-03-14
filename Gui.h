#include <gtk/gtk.h>
class Gui
{
	public:
		void Load();
	protected:
		static void Submit(GtkWidget *widget, gpointer label);
		static void CB_Checked(GtkWidget *widget, gpointer window);
	
};
