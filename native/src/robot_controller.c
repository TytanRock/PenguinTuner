#include "robot_controller.h"
#include "server_requests.h"

static struct {
    GtkEntry *server_ip_entry;
    GtkEntry *server_port_entry;
    GtkTextBuffer *controller_status_buffer;
}_module;

void react_btn_run_temporary_diag_server(GtkWidget *widget, gpointer data)
{
    gtk_text_buffer_set_text(_module.controller_status_buffer, "Hello World!", -1);
    get_devices(NULL, 0);
}

void add_txt_server_ip_entry(GtkEntry *entry)
{
    _module.server_ip_entry = entry;
}

void add_txt_server_port_entry(GtkEntry *entry)
{
    _module.server_port_entry = entry;
}

void add_txt_controller_status_buffer(GtkTextBuffer *buffer)
{
    _module.controller_status_buffer = buffer;
}
