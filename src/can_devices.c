#include <stdio.h>

#include "app_callbacks.h"
#include "can_devices.h"
#include "robot_controller.h"
#include <string.h>

static struct
{
    GtkTreeSelection *device_selector;
    GtkLabel *selected_device_label;
    GtkSpinButton *txt_dev_id;
    GtkFileChooserButton *btn_firmware_file;
    GtkEntry *txt_device_name;

    can_device_t selected_device;
}_module;

void update_lbl();

void add_slct_device_selection(GtkTreeSelection *selector)
{
    _module.device_selector = selector;
    _module.selected_device.id = -1; // Initialize selected device here as well for the moment
}

void add_lbl_selected_device(GtkLabel *lbl)
{
    _module.selected_device_label = lbl;
}

void add_txt_change_id(GtkSpinButton *idTxt)
{
    _module.txt_dev_id = idTxt;
}

void add_btn_firmware_file(GtkFileChooserButton *btn)
{
    _module.btn_firmware_file = btn;
}

void add_txt_device_name(GtkEntry *entry)
{
    _module.txt_device_name = entry;
}


can_device_t get_selected_device()
{
    return _module.selected_device;
}
void set_selected_device(can_device_t newDevice)
{
    _module.selected_device = newDevice;
    update_lbl();
}

void update_lbl()
{
    /* Update label with our selected device */
    char labelString[100];
    sprintf(labelString, "Selected Device:\n%s %d", _module.selected_device.model, _module.selected_device.id);
    gtk_label_set_text(_module.selected_device_label, labelString);
}

void react_changed_device(GtkWidget *widget, gpointer data)
{
    /* We need to find the row in the treeselector that the user selected */
    GtkTreeModel *tree;
    GtkTreeIter iter;
    if(gtk_tree_selection_get_selected(_module.device_selector, &tree, &iter))
    {
        {
            GValue value = G_VALUE_INIT;
            gtk_tree_model_get_value(tree, &iter, 0, &value); /* Device Name */
            strcpy(_module.selected_device.name, g_value_get_string(&value));
            gtk_entry_set_text(_module.txt_device_name, g_value_get_string(&value));
            g_value_unset(&value);
        }
        {
            GValue value = G_VALUE_INIT;
            gtk_tree_model_get_value(tree, &iter, 2, &value); /* Hardware */
            strcpy(_module.selected_device.model, g_value_get_string(&value));
            g_value_unset(&value);
        }
        {
            GValue value = G_VALUE_INIT;
            gtk_tree_model_get_value(tree, &iter, 3, &value); /* Device ID */
            _module.selected_device.id = g_value_get_int(&value);
            g_value_unset(&value);
        }
        update_lbl();
    } else {
        _module.selected_device.id = -1;
    }
}

void react_changed_id(GtkWidget *widget, gpointer data)
{
    /* Check we have a device selected */
    if(_module.selected_device.id != -1)
    {
        int newId = gtk_spin_button_get_value_as_int(_module.txt_dev_id);
        if(set_device_id(&_module.selected_device, newId, frontend_callback) == 0)
        {
            // Nothing
        }
    }
}

void react_update_firmware(GtkWidget *widget, gpointer data)
{
    const char *firmware_file = gtk_file_chooser_get_filename((GtkFileChooser *)_module.btn_firmware_file);
    upload_style style;
    char ssh_username[100];
    char ssh_password[100];

    get_upload_style_parameters(&style, ssh_username, ssh_password);

    update_device_firmware(&_module.selected_device, firmware_file, frontend_update_firm_status, frontend_callback, style, ssh_username, ssh_password);
}

void react_changed_name(GtkWidget *widget, gpointer data)
{
    const char *new_name = gtk_entry_get_text(_module.txt_device_name);
    set_device_name(&_module.selected_device, new_name, frontend_callback);
}
void react_blink_device(GtkWidget *widget, gpointer data)
{
    blink_device(&_module.selected_device, frontend_callback);
}
void react_snapshot_device(GtkWidget *widget, gpointer data)
{
    get_device_snapshot(&_module.selected_device, frontend_callback);
}
void react_default_device(GtkWidget *widget, gpointer data)
{
    factory_default_device(&_module.selected_device, frontend_callback);
}

