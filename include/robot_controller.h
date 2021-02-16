#ifndef __ROBOT_CONTROLLER_H__
#define __ROBOT_CONTROLLER_H__

#include <gtk/gtk.h>
#include "backend.h"

void react_btn_run_temporary_diag_server(GtkWidget *widget, gpointer data);

void react_server_ip_change(GtkWidget *widget, gpointer data);

void react_use_post_select(GtkWidget *widget, gpointer data);
void react_use_ssh_select(GtkWidget *widget, gpointer data);

void add_txt_server_ip_entry(GtkEntry *entry);

void add_txt_server_port_entry(GtkEntry *entry);

void add_use_ssh_menuitem(GtkCheckMenuItem *menuitem);
void add_use_post_menuitem(GtkCheckMenuItem *menuitem);
void add_txt_ssh_password_entry(GtkEntry *entry);
void add_txt_ssh_username_entry(GtkEntry *entry);

void add_txt_controller_status_buffer(GtkTextBuffer *buffer);

void get_upload_style_parameters(upload_style *style, char *username, char *password);

#endif
