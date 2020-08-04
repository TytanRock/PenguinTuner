#ifndef __ROBOT_CONTROLLER_H__
#define __ROBOT_CONTROLLER_H__

#include <gtk/gtk.h>

void react_btn_run_temporary_diag_server(GtkWidget *widget, gpointer data);

void react_server_ip_change(GtkWidget *widget, gpointer data);

void add_txt_server_ip_entry(GtkEntry *entry);

void add_txt_server_port_entry(GtkEntry *entry);

void add_txt_controller_status_buffer(GtkTextBuffer *buffer);

#endif
