#include "robot_controller.h"
#include "backend.h"
#include <string.h>

#define MAX_IP_SIZE 40

static struct {
    GtkEntry *server_ip_entry;
    GtkEntry *server_port_entry;
    GtkEntry *ssh_username_entry;
    GtkEntry *ssh_password_entry;

    GtkCheckMenuItem *use_post_menuitem;
    GtkCheckMenuItem *use_ssh_menuitem;

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

void add_txt_ssh_username_entry(GtkEntry *entry)
{
    _module.ssh_username_entry = entry;
}

void add_txt_ssh_password_entry(GtkEntry *entry)
{
    _module.ssh_password_entry = entry;
}

void add_use_post_menuitem(GtkCheckMenuItem *menuitem)
{
    _module.use_post_menuitem = menuitem;
}

void add_use_ssh_menuitem(GtkCheckMenuItem *menuitem)
{
    _module.use_ssh_menuitem = menuitem;
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

void react_use_post_select(GtkWidget *widget, gpointer data)
{
    if(gtk_check_menu_item_get_active((GtkCheckMenuItem *)widget))
    {
        gtk_check_menu_item_set_active(_module.use_post_menuitem, TRUE);
        gtk_check_menu_item_set_active(_module.use_ssh_menuitem, FALSE);
    }
}

void react_use_ssh_select(GtkWidget *widget, gpointer data)
{
    if(gtk_check_menu_item_get_active((GtkCheckMenuItem *)widget))
    {
        gtk_check_menu_item_set_active(_module.use_ssh_menuitem, TRUE);
        gtk_check_menu_item_set_active(_module.use_post_menuitem, FALSE);
    }
}

void get_upload_style_parameters(upload_style *style, char *username, char *password)
{
    upload_style usedStyle = POST;
    if(gtk_check_menu_item_get_active(_module.use_post_menuitem))
    {
        usedStyle = POST;
    }
    else if(gtk_check_menu_item_get_active(_module.use_ssh_menuitem))
    {
        usedStyle = SSH;
    }
    *style = usedStyle;
    strcpy(username, gtk_entry_get_text(_module.ssh_username_entry));
    strcpy(password, gtk_entry_get_text(_module.ssh_password_entry));
}
