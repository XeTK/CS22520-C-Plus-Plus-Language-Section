#include <gtk/gtk.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include "Gui.h"
#include "Entrant.h"
#include "Course.h"
#include "Node.h"
#include "FileReader.h"

using namespace std;
static GtkWidget *window, *frame, *submit_but, *arival_box, *depart_box, *node_box, *timemed_cb, *user_db, *user_lbl, *arival_lbl, *depart_lbl, *cp_lbl;
static vector<Entrant> glob_entrants;
static int number_of_nodes = 0;
static string time_file;
Gui::Gui(string save_path, string entrant_path, string course_path, string node_path)
{
        time_file = save_path;
        FileReader fr;
        glob_entrants = fr.get_entrants(entrant_path.c_str(),course_path.c_str(),node_path.c_str());
}
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
	
        for (int i = 0; i < glob_entrants.size();i++)
                gtk_combo_box_append_text(GTK_COMBO_BOX(user_db), glob_entrants[i].get_name().c_str());
	
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
	
	gtk_widget_set_size_request(node_box, 95, 25);
	gtk_fixed_put(GTK_FIXED(frame), node_box, 125, 65);
	
	//time_radio
	timemed_cb = gtk_check_button_new_with_label("Medical Check Point");
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
        g_signal_connect(user_db, "changed", G_CALLBACK(Gui::combo_selected), NULL);
        g_signal_connect(timemed_cb, "clicked", G_CALLBACK(Gui::combo_selected),NULL);
	gtk_main();
}

void Gui::Submit(GtkWidget *widget, gpointer label)
{
        string line;
        char times[5];
        char node;
        int entrant;
        
        time_t now = time(0);
        tm *gmtm = gmtime(&now);
        sprintf(times,"%d:%d",gmtm->tm_hour,gmtm->tm_min);
        
        const char *ari = gtk_entry_get_text(GTK_ENTRY(arival_box));
        if (gtk_entry_get_text_length(GTK_ENTRY(arival_box)) > 0)
            sprintf(times,"%s",ari);
        
        if (GTK_TOGGLE_BUTTON (timemed_cb)->active)
            node = 'A';
        else
            node = 'T';
        
        gchar *tnode = gtk_combo_box_get_active_text(GTK_COMBO_BOX(node_box));
        
        gchar *tentrant =  gtk_combo_box_get_active_text(GTK_COMBO_BOX(user_db));
        
        for (int i = 0; i < glob_entrants.size();i++)
        {
            if (glob_entrants[i].get_name() == tentrant)
            {
                entrant = glob_entrants[i].get_entrant_no();
                break;
            }
        }
        char buff[100];
        sprintf(buff,"%c %s %d %s\n",node,tnode,entrant,times);
        line = buff;
        if (GTK_TOGGLE_BUTTON (timemed_cb)->active) 
        {
            const char *dep = gtk_entry_get_text(GTK_ENTRY(depart_box));
            if (gtk_entry_get_text_length(GTK_ENTRY(depart_box)) > 0)
                sprintf(times,"%s",dep);
            sprintf(buff,"%c %s %d %s\n",'D',tnode,entrant,times);
            line += buff;
        }
        FileReader fr;
        fr.add_to_file(time_file.c_str(),line);
        cout << "Added : " << line << "To " << time_file << " File\n";
        message_box(window,"Success","The File Has been written here");
}
void Gui::combo_selected(GtkWidget *widget, gpointer window)
{ 
        gchar *text =  gtk_combo_box_get_active_text(GTK_COMBO_BOX(user_db));
        for (int i = 0; i < number_of_nodes; i++)
            gtk_combo_box_remove_text(GTK_COMBO_BOX(node_box),0);
        
        number_of_nodes = 0;
        
        for (int i = 0; i < glob_entrants.size();i++)
        {
            if (glob_entrants[i].get_name() == text)
            {
                vector<Node> t_n = glob_entrants[i].get_course().get_nodes();
                for (int j = 0;j < t_n.size();j++)
                {
                        if (GTK_TOGGLE_BUTTON (timemed_cb)->active) 
                        {
                            gtk_widget_set_sensitive(depart_box,true);
                            if (t_n[j].get_nodetype() == "MC")
                            {
                                char c_n[2];
                                sprintf(c_n, "%d", t_n[j].get_node());
                                number_of_nodes++;
                                gtk_combo_box_append_text(GTK_COMBO_BOX(node_box), c_n);
                            }
                        }
                        else
                        {
                            gtk_widget_set_sensitive(depart_box,false);
                            if (t_n[j].get_nodetype() == "CP")
                            {
                                char c_n[2];
                                sprintf(c_n, "%d", t_n[j].get_node());
                                number_of_nodes++;
                                gtk_combo_box_append_text(GTK_COMBO_BOX(node_box), c_n);
                            }
                        }		                                            
                }
                break;
            }
        }
        g_free(text);
}
void Gui::message_box(GtkWidget* thisparent, const char* dtitle, const char* dmessage)
{
	GtkWidget* msg_box = gtk_dialog_new_with_buttons(dtitle, GTK_WINDOW(thisparent),
		GTK_DIALOG_DESTROY_WITH_PARENT,GTK_STOCK_OK,GTK_RESPONSE_NONE,0);
	
	g_signal_connect_swapped(msg_box, "response", G_CALLBACK(gtk_widget_destroy),msg_box);
		
	GtkWidget* msgLabel = gtk_label_new(dmessage);
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(msg_box)->vbox), msgLabel);

	gtk_widget_show_all(msg_box);
}
