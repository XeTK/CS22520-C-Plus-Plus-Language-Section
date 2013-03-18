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
//This class contains the basis of the gui for the program, it is all written in GTK2.0
using namespace std;
//Decleration of are widgets they are static so we can refer back to them  later when things change
static GtkWidget *window, *frame, *submit_but, *arival_box, *depart_box, *node_box, *timemed_cb, *user_db, *user_lbl, *arival_lbl, *depart_lbl, *cp_lbl;
//hold the vector of the global entrants that we are using for refrancing back to
static vector<Entrant> glob_entrants;
//hold the number of nodes so we can clear them later. as gtk does not have a clear combobox method
static int number_of_nodes = 0;
//hold the origernal time file path
static string time_file;
//load in the files from outside the program for later use
Gui::Gui(string save_path, string entrant_path, string course_path, string node_path)
{
        //set the path of the times file that we will be working on
        time_file = save_path;
        //open a file reader to get the contents of are files
        FileReader fr;
        //read the entrants into the vector for later use
        glob_entrants = fr.get_entrants(entrant_path.c_str(),course_path.c_str(),node_path.c_str());
}
//this is the method that is called to create are new gui
void Gui::Load()
{
        //create a new window for us to add things to
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        //set the title of the window we are going to be using
	gtk_window_set_title(GTK_WINDOW(window), "CheckPoint Manger");
        //set the size of the window we are going to be using
	gtk_window_set_default_size(GTK_WINDOW(window), 250, 250);
        //put are window dead center in the middle of the screen so it is easy to see
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	
        //create a frame to add are widgets to
	frame = gtk_fixed_new();
        //add the frame to the window so we have something to work with
	gtk_container_add(GTK_CONTAINER(window), frame);
        
	//Next we create a submit button
	submit_but = gtk_button_new_with_label("Submit");
        //set its size 
	gtk_widget_set_size_request(submit_but, 200, 35);
        //set its position and add it to the frame we created earlier
	gtk_fixed_put(GTK_FIXED(frame), submit_but, 20, 180);
	
	//Now we create a user Combo Box
	user_db = gtk_combo_box_new_text();
	
        //add are entrants to the box for use to select later
        for (int i = 0; i < glob_entrants.size();i++)
                gtk_combo_box_append_text(GTK_COMBO_BOX(user_db), glob_entrants[i].get_name().c_str());
	
        //Set the size
	gtk_widget_set_size_request(user_db, 200, 35);
        //Set the position and add it to the frame
	gtk_fixed_put(GTK_FIXED(frame), user_db, 20, 25);
	
        //we basicly do the same thing for the next few widgets
        //1 Declare
        //2 Size
        //3 Add to frame & Posision
        
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
	
        //now we display the widgets on screen and present the window to the end user
	gtk_widget_show_all(window);
        //we now connect the buttons/widgets to some methods to handle different events
        //this one destroys the object on the distruction of the main window
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
        //this is the one to tie in the end submit button to add are results to the times file
	g_signal_connect(submit_but, "clicked", G_CALLBACK(Gui::Submit), NULL);	
        //the next to are to monitor the changes in the combo box selections
        g_signal_connect(user_db, "changed", G_CALLBACK(Gui::combo_selected), NULL);
        g_signal_connect(node_box, "changed", G_CALLBACK(Gui::node_combo_selected), NULL);
        //this is to disable the other textbox and update nodebox when there is only medical checkpoints in use
        g_signal_connect(timemed_cb, "clicked", G_CALLBACK(Gui::combo_selected),NULL);
        //this disables the submit button till later
        gtk_widget_set_sensitive(submit_but,false);
        //this calls the gtk main method to be called displaying the final window
	gtk_main();
}
//event handler for the submit button
void Gui::Submit(GtkWidget *widget, gpointer label)
{
        //hold some temporay values for the things to be added to the file at the end
        string line;
        char times[5];
        char node;
        int entrant;
        
        //get the current time
        time_t now = time(0);
        tm *gmtm = gmtime(&now);
        //convert it to a string
        sprintf(times,"%d:%d",gmtm->tm_hour,gmtm->tm_min);
        
        //get the text from the textbox for arival
        const char *ari = gtk_entry_get_text(GTK_ENTRY(arival_box));
        //if the text is null then set the arival time to the current time
        if (gtk_entry_get_text_length(GTK_ENTRY(arival_box)) > 0)
            sprintf(times,"%s",ari);
        
        //decide if the node that we are at is a medical or just a checkpoint
        if (GTK_TOGGLE_BUTTON (timemed_cb)->active)
            node = 'A';
        else
            node = 'T';
        
        //get the text from the current node
        gchar *tnode = gtk_combo_box_get_active_text(GTK_COMBO_BOX(node_box));
        
        //get the current entrant
        gchar *tentrant =  gtk_combo_box_get_active_text(GTK_COMBO_BOX(user_db));
        
        //convert the current entrants name into there entrant number
        for (int i = 0; i < glob_entrants.size();i++)
        {
            if (glob_entrants[i].get_name() == tentrant)
            {
                entrant = glob_entrants[i].get_entrant_no();
                break;
            }
        }
        //hold a buffer for the string that we are building
        char buff[100];
        //add the values to a line for later
        sprintf(buff,"%c %s %d %s\n",node,tnode,entrant,times);
        //pass the buffer over to the origernal string
        line = buff;
        //if this is a medical checkpoint then we have to add in the departure time
        if (GTK_TOGGLE_BUTTON (timemed_cb)->active) 
        {
            //get the text from the departure
            const char *dep = gtk_entry_get_text(GTK_ENTRY(depart_box));
            //if the text is null then set the departure time to the current time
            if (gtk_entry_get_text_length(GTK_ENTRY(depart_box)) > 0)
                sprintf(times,"%s",dep);
            //build are string
            sprintf(buff,"%c %s %d %s\n",'D',tnode,entrant,times);
            //add it to the line to be printed
            line += buff;
        }
        //open the filewritter
        FileReader fr;
        //add the line to the end of the times file
        fr.add_to_file(time_file.c_str(),line);
        //print out some debug so we can see what we added and if its correct
        cout << "Added : " << line << "To " << time_file << " File\n";
        //show a messagebox for the end user's feedback so they know the task has been done
        message_box(window,"Success","The File Has been written here");
}
//for the change in selection of a combo box
void Gui::combo_selected(GtkWidget *widget, gpointer window)
{ 
        //get the text from the combo box
        gchar *text =  gtk_combo_box_get_active_text(GTK_COMBO_BOX(user_db));
        //clear the node box
        for (int i = 0; i < number_of_nodes; i++)
            gtk_combo_box_remove_text(GTK_COMBO_BOX(node_box),0);
        //reset the number of nodes
        number_of_nodes = 0;
        //loop through the entrants
        for (int i = 0; i < glob_entrants.size();i++)
        {
            //find the one thats the same name as the entrants box
            if (glob_entrants[i].get_name() == text)
            {
                //get the nodes from that entrant
                vector<Node> t_n = glob_entrants[i].get_course().get_nodes();
                for (int j = 0;j < t_n.size();j++)
                {
                        //if the medical point is ticked then we add the medical nodes to the nodes box
                        if (GTK_TOGGLE_BUTTON (timemed_cb)->active) 
                        {
                            //enable the departure box seeing as we are doing medical nodes
                            gtk_widget_set_sensitive(depart_box,true);
                            //only add nodes if they are medical
                            if (t_n[j].get_nodetype() == "MC")
                            {
                                //convert the node number to a char array as the messageboxes throw a fit otherwise...
                                char c_n[2];
                                sprintf(c_n, "%d", t_n[j].get_node());
                                //increment the number of nodes we have otherwise we cant erase them later
                                number_of_nodes++;
                                //add the node to the combo box
                                gtk_combo_box_append_text(GTK_COMBO_BOX(node_box), c_n);
                            }
                        }
                        else
                        {
                            //if we are not doing medical checkpoints disable departure box
                            gtk_widget_set_sensitive(depart_box,false);
                            //only add nodes that are checkpoints to the node box
                            if (t_n[j].get_nodetype() == "CP")
                            {
                                //convert the int to a char array for the text box as they dont like int values
                                char c_n[2];
                                sprintf(c_n, "%d", t_n[j].get_node());
                                number_of_nodes++;
                                //add the node to the box
                                gtk_combo_box_append_text(GTK_COMBO_BOX(node_box), c_n);
                            }
                        }		                                            
                }
                //one we have added the nodes then break away as are work is done
                break;
            }
        }
        //free the pointer from the text
        g_free(text);
}
//Check if the node combo box is valid
void Gui::node_combo_selected(GtkWidget *widget, gpointer window)
{ 
        //get the text from the combo box
        gchar *text =  gtk_combo_box_get_active_text(GTK_COMBO_BOX(node_box));
        //if the text is nothing then we 
        if (text == NULL)
        {
            //we disable the submit button to stop any problems
            gtk_widget_set_sensitive(submit_but,false);
        }
        else
        {
            //else we let them use it
            gtk_widget_set_sensitive(submit_but,true);
        }
}
//Simple method to create a message box for the end user to see
void Gui::message_box(GtkWidget* thisparent, const char* dtitle, const char* dmessage)
{
        //create a new dialog for the end user to see
	GtkWidget* msg_box = gtk_dialog_new_with_buttons(dtitle, GTK_WINDOW(thisparent),
		GTK_DIALOG_DESTROY_WITH_PARENT,GTK_STOCK_OK,GTK_RESPONSE_NONE,0);
	//add event handler to close the box if the button is pressed
	g_signal_connect_swapped(msg_box, "response", G_CALLBACK(gtk_widget_destroy),msg_box);
        //add a label with are message
	GtkWidget* msgLabel = gtk_label_new(dmessage);
        //add the widgets to the containier
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(msg_box)->vbox), msgLabel);
        //show are messagebox to the end user
	gtk_widget_show_all(msg_box);
}
