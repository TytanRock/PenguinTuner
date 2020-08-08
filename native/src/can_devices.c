#include <stdio.h>

#include "app_callbacks.h"
#include "can_devices.h"

static struct
{
    GtkTreeSelection *device_selector;
    GtkLabel *selected_device_label;

    can_device_t selected_device;
}_module;

void add_slct_device_selection(GtkTreeSelection *selector)
{
    _module.device_selector = selector;
}

void add_lbl_selected_device(GtkLabel *lbl)
{
    _module.selected_device_label = lbl;
}

can_device_t get_selected_device()
{
    return _module.selected_device;
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
    }
}

