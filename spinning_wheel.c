#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>

#define WHEEL_SIZE 400

typedef struct {
    double angle;
    int spinning;
    GtkWidget *drawing_area;
} WheelState;

gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    WheelState *state = (WheelState*)user_data;
    
    printf("Drawing wheel. Angle: %f\n", state->angle);
    
    // Set up the drawing area
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    
    // Move to the center of the drawing area
    cairo_translate(cr, WHEEL_SIZE/2, WHEEL_SIZE/2);
    
    // Rotate based on current angle
    cairo_rotate(cr, state->angle);
    
    // Draw the wheel (simplified)
    cairo_set_source_rgb(cr, 0, 0.5, 0);
    cairo_arc(cr, 0, 0, WHEEL_SIZE/2 - 10, 0, 2 * M_PI);
    cairo_fill(cr);
    
    // Draw some lines to represent slots
    cairo_set_source_rgb(cr, 1, 1, 1);
    for (int i = 0; i < 37; i++) {
        cairo_move_to(cr, 0, 0);
        cairo_line_to(cr, 0, WHEEL_SIZE/2 - 10);
        cairo_stroke(cr);
        cairo_rotate(cr, 2 * M_PI / 37);
    }
    
    return FALSE;
}

gboolean update_wheel(gpointer user_data) {
    WheelState *state = (WheelState*)user_data;
    if (state && state->spinning) {
        state->angle += 0.1;
        if (state->angle > 2 * M_PI) {
            state->angle -= 2 * M_PI;
        }
        printf("Updating wheel. Angle: %f\n", state->angle);
        if (state->drawing_area) {
            gtk_widget_queue_draw(state->drawing_area);
        }
    }
    return TRUE;  // Always return TRUE to keep the timer running
}

int main(int argc, char *argv[]) {
    if (!gtk_init_check(&argc, &argv)) {
        fprintf(stderr, "Failed to initialize GTK\n");
        return 1;
    }
    
    printf("GTK initialized\n");
    
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    if (!window) {
        fprintf(stderr, "Failed to create window\n");
        return 1;
    }
    
    printf("Window created\n");
    
    GtkWidget *drawing_area = gtk_drawing_area_new();
    if (!drawing_area) {
        fprintf(stderr, "Failed to create drawing area\n");
        return 1;
    }
    
    printf("Drawing area created\n");
    
    WheelState *state = g_new(WheelState, 1);
    state->angle = 0;
    state->spinning = 1;
    state->drawing_area = drawing_area;
    
    gtk_widget_set_size_request(drawing_area, WHEEL_SIZE, WHEEL_SIZE);
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw), state);
    
    gtk_container_add(GTK_CONTAINER(window), drawing_area);
    
    g_timeout_add(50, update_wheel, state);
    
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all(window);
    
    printf("Starting main loop\n");
    gtk_main();
    
    printf("Main loop ended\n");
    
    g_free(state);
    
    return 0;
}
