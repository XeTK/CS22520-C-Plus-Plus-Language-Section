#include <gtk/gtk.h>
using namespace std;
class Gui
{
	public:
		void Load();
	protected:
		static void Submit(GtkWidget *widget, gpointer label);
		static void CB_Checked(GtkWidget *widget, gpointer window);
	
};
