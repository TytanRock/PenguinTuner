#include <stdio.h>

#include "app_callbacks.h"
#include "can_devices.h"

static struct
{
    GtkTreeSelection *device_selector;
    GtkLabel *selected_device_label;
    GtkSpinButton *txt_dev_id;
    GtkFileChooserButton *btn_firmware_file;

    can_device_t selected_device;
}_module;

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

can_device_t get_selected_device()
{
    return _module.selected_device;
}

void react_changed_id(GtkWidget *widget, gpointer data)
{
    /* Check we have a device selected */
    if(_module.selected_device.id != -1)
    {
        int newId = gtk_spin_button_get_value_as_int(_module.txt_dev_id);
        set_device_id(&_module.selected_device, newId);
    }
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
            g_value_unset(&value);
        }
        {
            GValue value = G_VALUE_INIT;
            gtk_tree_model_get_value(tree, &iter, 2, &value); /* Device Name */
            strcpy(_module.selected_device.model, g_value_get_string(&value));
            g_value_unset(&value);
        }
        {
            GValue value = G_VALUE_INIT;
            gtk_tree_model_get_value(tree, &iter, 3, &value); /* Device Name */
            _module.selected_device.id = g_value_get_int(&value);
            g_value_unset(&value);
        }
        /* Update label with our selected device */
        char labelString[100];
        sprintf(labelString, "Selected Device:\n%s |Model: %s ID: %d|", _module.selected_device.name, _module.selected_device.model, _module.selected_device.id);
        gtk_label_set_text(_module.selected_device_label, labelString);
    } else {
        _module.selected_device.id = -1;
    }
}

void react_update_firmware(GtkWidget *widget, gpointer data)
{
    const char *firmware_file = gtk_file_chooser_get_filename((GtkFileChooser *)_module.btn_firmware_file);

    printf("File: %s\n", firmware_file);
}

