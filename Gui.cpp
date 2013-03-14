#include <gtk/gtk.h>
#include "Gui.h"
static GtkWidget *window, *frame, *submit_but, *arival_box, *depart_box, *node_box, *timemed_cb, *user_db, *user_lbl, *arival_lbl, *depart_lbl, *cp_lbl;

void Gui::Load()
{
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "CheckPoint Manger");
	gtk_window_set_default_size(GTK_WINDOW(window), 250, 250);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	
	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), frame);
	//submit button
	submit_but = gtk_button_new_with_label("Submit");
	gtk_widget_set_size_request(submit_but, 200, 35);
	gtk_fixed_put(GTK_FIXED(frame), submit_but, 20, 180);
	
	//user Combo Box
	user_db = gtk_combo_box_new_text();
	
	gtk_combo_box_append_text(GTK_COMBO_BOX(user_db), "BLAH");
	gtk_combo_box_append_text(GTK_COMBO_BOX(user_db), "BLAH1");
	
	gtk_widget_set_size_request(user_db, 200, 35);
	gtk_fixed_put(GTK_FIXED(frame), user_db, 20, 25);
	
	//textbox arival
	arival_box = gtk_entry_new();
	gtk_widget_set_size_request(arival_box, 95, 25);
	gtk_fixed_put(GTK_FIXED(frame), arival_box, 20, 150);

	//textbox depart
	depart_box = gtk_entry_new();
	gtk_widget_set_size_request(depart_box, 95, 25);
	gtk_fixed_put(GTK_FIXED(frame), depart_box, 125, 150);

	//node box
	node_box = gtk_combo_box_new_text();
	
	gtk_combo_box_append_text(GTK_COMBO_BOX(node_box), "1");
	gtk_combo_box_append_text(GTK_COMBO_BOX(node_box), "2");


	gtk_widget_set_size_request(node_box, 95, 25);
	gtk_fixed_put(GTK_FIXED(frame), node_box, 125, 65);
	
	//time_radio
	timemed_cb = gtk_check_button_new_with_label("Medical Check Point");
//	gtk_widget_set_size_request(timemed_cb, 95,25);
	gtk_fixed_put(GTK_FIXED(frame), timemed_cb, 20, 110);


	//labels
	user_lbl = gtk_label_new("Entrants");
	arival_lbl = gtk_label_new("Arival");
	depart_lbl = gtk_label_new("Depart");
	cp_lbl = gtk_label_new("Check Point");
	
	gtk_widget_set_size_request(user_lbl, 50,25);
        gtk_widget_set_size_request(arival_lbl, 50,25);
        gtk_widget_set_size_request(depart_lbl, 50,25);
	
	gtk_fixed_put(GTK_FIXED(frame), user_lbl, 20, 5);
	gtk_fixed_put(GTK_FIXED(frame), arival_lbl, 20, 130);
	gtk_fixed_put(GTK_FIXED(frame), depart_lbl, 125, 130);
	gtk_fixed_put(GTK_FIXED(frame), cp_lbl, 20, 70);
	
	gtk_widget_show_all(window);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(submit_but, "clicked", G_CALLBACK(Gui::Submit), NULL);	
	gtk_main();
}

void Gui::Submit(GtkWidget *widget, gpointer label)
{
	gchar *node = gtk_combo_box_get_active_text(GTK_COMBO_BOX(node_box));
	printf("%s\n",node);

	gchar *checkbox =  gtk_combo_box_get_active_text(GTK_COMBO_BOX(user_db));
        printf("%s\n",checkbox);

	const char *dep = gtk_entry_get_text(GTK_ENTRY(depart_box));
	printf("%s\n",dep);
	
	const char *ari = gtk_entry_get_text(GTK_ENTRY(arival_box));
	printf("%s\n",ari);

	if (GTK_TOGGLE_BUTTON (timemed_cb)->active) 
		printf("Lemons\n");
	else
		printf("Limes\n");
}
