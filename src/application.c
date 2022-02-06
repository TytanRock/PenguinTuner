#include <stdio.h>
#include <gtk/gtk.h>

#include "backend.h"
#include "form_maker.h"

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("com.tytanrock.penguintuner", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK(create_form), NULL);

    start_backend();
    int stat = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return stat;
}
