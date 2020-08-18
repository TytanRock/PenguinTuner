#include <stdio.h>
#include <gtk/gtk.h>

#include "app_callbacks.h"

int main(int argc, char **argv) {

    gtk_init(&argc, &argv);
    
    connect_all_signals();

    gtk_main();

    return 0;
}
