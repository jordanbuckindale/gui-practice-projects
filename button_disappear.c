/* 
-----------------------------------------------------
Jordan Buckindale
Date: July 18 2024

A program that creates a simple GUI.
-----------------------------------------------------
*/
#include <gtk/gtk.h>

int main(int argc, char *argv[]) {

    // declare variables.
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box;

    // initializes the GTK library.
    gtk_init(&argc, &argv);

    // create window.
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Simple GUI");

    // create box container.
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);

    // create button.
    button = gtk_button_new_with_label("Click Me");
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);

    // create signals. 
    g_signal_connect(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // show all widgets.
    gtk_widget_show_all(window);
    gtk_main();

    // exit program.
    return 0;
}
