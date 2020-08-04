#include "robot_controller.h"
#include "backend.h"

#define MAX_IP_SIZE 40

static struct {
    GtkEntry *server_ip_entry;
    GtkEntry *server_port_entry;
    GtkTextBuffer *controller_status_buffer;
}_module;

void react_btn_run_temporary_diag_server(GtkWidget *widget, gpointer data)
{
    gtk_text_buffer_set_text(_module.controller_status_buffer, "Hello World!", -1);
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

void react_server_ip_change(GtkWidget *widget, gpointer data)
{
    /* Allocate some space to do stringwork */
    char fullIp[MAX_IP_SIZE];
    strncpy(fullIp, gtk_entry_get_text(_module.server_ip_entry), MAX_IP_SIZE);
    /* Trim everything after the '#' */
    char *startOfComment = strstr(fullIp, "#");
    if(startOfComment == NULL)
    {
        /* Set startOfComment to end of string instead */
        startOfComment = fullIp + strlen(fullIp);
    }
    /* Found the end, back up one */
    --startOfComment;
    /* Trim whitespace before the comment character as well */
    while(fullIp[startOfComment - fullIp] == ' ' && startOfComment >= fullIp) {
        --startOfComment;
    }
    /* We found the end of the valid IP, make sure it's the end by null-terminating the next character */
    fullIp[startOfComment + 1 - fullIp] = '\0';
    
    /* Now concatenate the port to the URI */
    strncat(fullIp, ":", MAX_IP_SIZE - strlen(fullIp));
    strncat(fullIp, gtk_entry_get_text(_module.server_port_entry), MAX_IP_SIZE - strlen(fullIp));
    
    /* And finally call into backend to set the ip */
    set_ip(fullIp);
}
