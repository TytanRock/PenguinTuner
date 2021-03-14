#ifndef __CAN_DEVICES_H__
#define __CAN_DEVICES_H__

#include <gtk/gtk.h>
#include "backend.h"

void add_slct_device_selection(GtkTreeSelection *selector);
void add_lbl_selected_device(GtkComboBox *cmbobx);
void add_txt_change_id(GtkSpinButton *idTxt);
void add_btn_firmware_file(GtkFileChooserButton *btn);
void add_txt_device_name(GtkEntry *entry);

void set_selected_device_treemodel(GtkTreeModel *treeModel);

can_device_t get_selected_device();

void react_changed_id(GtkWidget *widget, gpointer data);
void update_fields_with_tree_selection(int hardUpdate);
void react_changed_device_from_treeview(GtkWidget *widget, gpointer data);
void react_changed_device_from_combobox(GtkWidget *widget, gpointer data);
void react_update_firmware(GtkWidget *widget, gpointer data);
void react_changed_name(GtkWidget *widget, gpointer data);
void react_blink_device(GtkWidget *widget, gpointer data);
void react_snapshot_device(GtkWidget *widget, gpointer data);
void react_default_device(GtkWidget *widget, gpointer data);

#endif

