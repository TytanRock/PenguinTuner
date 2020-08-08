#ifndef __CAN_DEVICES_H__
#define __CAN_DEVICES_H__

#include <gtk/gtk.h>
#include "backend.h"

void add_slct_device_selection(GtkTreeSelection *selector);

void add_lbl_selected_device(GtkLabel *lbl);

can_device_t get_selected_device();

void react_changed_device(GtkWidget *widget, gpointer data);

#endif

