#include <gtk/gtk.h>
#include "Gui.h"
void Gui::Load()
{
	GtkWidget *window, *frame, *submit_but, *arival_box, *depart_box, *node_box, *time_cb, *med_cb, *user_db, *user_lbl, *arival_lbl, *depart_lbl, *radio, *cp_lbl;

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
	node_box = gtk_entry_new();
	gtk_widget_set_size_request(node_box, 95, 25);
	gtk_fixed_put(GTK_FIXED(frame), node_box, 125, 65);
	
	//med_radio
	med_cb = gtk_radio_button_new_with_label(NULL,"Medical");
	gtk_widget_set_size_request(med_cb, 95,25);
	gtk_fixed_put(GTK_FIXED(frame), med_cb, 125, 110);

	//time_radio
	time_cb = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(med_cb),"Time");
	gtk_widget_set_size_request(time_cb, 95,25);
	gtk_fixed_put(GTK_FIXED(frame), time_cb, 20, 110);


	//labels
	user_lbl = gtk_label_new("Entrants");
	arival_lbl = gtk_label_new("Arival");
	depart_lbl = gtk_label_new("Depart");
	radio = gtk_label_new("Check Point type");
	cp_lbl = gtk_label_new("Check Point");
	
	gtk_widget_set_size_request(user_lbl, 50,25);
        gtk_widget_set_size_request(arival_lbl, 50,25);
        gtk_widget_set_size_request(depart_lbl, 50,25);
/*	gtk_widget_set_size_request(radio,150,25);
	gtk_widget_set_size_request(cp_lbl,150,25);
*/	
	gtk_fixed_put(GTK_FIXED(frame), user_lbl, 20, 5);
	gtk_fixed_put(GTK_FIXED(frame), arival_lbl, 20, 130);
	gtk_fixed_put(GTK_FIXED(frame), depart_lbl, 125, 130);
	gtk_fixed_put(GTK_FIXED(frame), radio, 20, 95);
	gtk_fixed_put(GTK_FIXED(frame), cp_lbl, 20, 70);
	
	gtk_widget_show_all(window);

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	//g_signal_connect(submit_but, "clicked", G_CALLBACK(Submit), NULL);	

	 //g_signal_connect(G_OBJECT(user_db), "changed", G_CALLBACK(combo_selected), (gpointer) label);

	gtk_main();
}

void Gui::Submit(GtkWidget *widget, gpointer label)
{
	printf("HelloWorld\n");
}
void Gui::combo_selected(GtkWidget *widget, gpointer window)
{ 
	gchar *text =  gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget));
	gtk_label_set_text(GTK_LABEL(window), text);
	g_free(text);
}
