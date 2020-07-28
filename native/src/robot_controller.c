#include "robot_controller.h"

static struct {
    GtkEntry *server_ip_entry;
}_module;

void react_btn_run_temporary_diag_server(GtkWidget *widget, gpointer data)
{
    gtk_entry_set_text(_module.server_ip_entry, "Hello World!");
}

void add_txt_server_ip_entry(GtkEntry *entry)
{
    _module.server_ip_entry = entry;
}

