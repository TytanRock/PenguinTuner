#ifndef __CAN_DEVICES_H__
#define __CAN_DEVICES_H__

#include <gtk/gtk.h>
#include "backend.h"

void add_slct_device_selection(GtkTreeSelection *selector);
void add_lbl_selected_device(GtkLabel *lbl);
void add_txt_change_id(GtkSpinButton *idTxt);
void add_btn_firmware_file(GtkFileChooserButton *btn);

can_device_t get_selected_device();
void set_selected_device(can_device_t newDevice);

void react_changed_id(GtkWidget *widget, gpointer data);
void react_changed_device(GtkWidget *widget, gpointer data);
void react_update_firmware(GtkWidget *widget, gpointer data);

#endif

