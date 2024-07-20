/* 
-----------------------------------------------------
Jordan Buckindale
Date: July 18 2024

A program that creates a simple GUI and outputs text to terminal.

Summary: 
A simple GTK application that sets up a window containing 
a box and button. When the button is clicked, a message is 
printed to the terminal. The program will exit whenever the 
window is closed.

Note:
I will be leaving detailed comments on each line of code
as reference to myself on the functions and variables and
how they operate within a GUI.

Steps to implementing:
1. -> import GTK library.
2. -> create main function.
    2.1 -> declare variables
    2.2 -> initialize GTK library
    2.3 -> create window
    2.4 -> create box container
    2.5 -> create button
    2.6 -> connect signals
    2.7 -> enable visiblity on widgets
    2.8 -> exit program
3. -> create callback function.
-----------------------------------------------------
*/

// imports the GTK header file which will provide the functions and types to the program.
#include<gtk/gtk.h>

static void on_button_clicked(GtkWidget *button, gpointer user_data);

/*
Main function where the main program will run.

This involves declaring nessecary variables, 
initializing the GTK library and creating the
window for the user to interact with.
*/
int main(int argc, char *argv[]) {
    
    // declare variables.
    GtkWidget *window; // pointer to main window widget.
    GtkWidget *button; // pointer to button widget.
    GtkWidget *box;    // pointer to box container widget.

    // initializes the GTK library.
    gtk_init(&argc, &argv);

    // create window.
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);           // creates a window on screen for the user to interact with.
    gtk_window_set_title(GTK_WINDOW(window), "Simple GUI"); // creates a title into the window saying "Simple GUI".

    // create box container.
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // creates a box container vertically. Parameters are direction and spacing measuring in pixels.
    gtk_container_add(GTK_CONTAINER(window), box);  // adds the box container into the window.

    // create button.
    button = gtk_button_new_with_label("Click Me");          // creates a button with label that says "Click Me".
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0); // adds the button to the box. Parameters 'True' indicate button should fill space and '0' specifies the padding.

    // connect signals. 
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL); // connects the action of user 'clicking' the button to the function 'on_button_clicked'.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);     // connects the action of user exiting or 'destroying' the window to the function 'gtk_main_quit' which will then exiit the GTK loop.

    // show all widgets.
    gtk_widget_show_all(window); // makes it so the window and buttons are visible on screen.
    gtk_main();                  // recursive loop which waits for user event (like button click) and triggers correct callback function.

    // exit program.
    return 0; 
}

// Function that will be called whenever user clicks button 'click me'.
static void on_button_clicked(GtkWidget *button, gpointer user_data) {
    
    // output.
    g_print("Button clicked\n"); // prints button clicked to the terminal.
}

