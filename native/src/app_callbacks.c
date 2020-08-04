#include "robot_controller.h"
#include "app_callbacks.h"
#include "backend.h"

#include <gtk/gtk.h>
#include <stdio.h>

#define MAX_DEVICE_COUNT 30

static struct
{
    /* All the devices that are available from backend */
    can_device_t devices[MAX_DEVICE_COUNT];
    int deviceCount;
    
    /* Gtk Widget references that matter */
    GtkListStore *deviceListStore;
    GtkTreeModel *deviceTreeModel;
}_module;

gint periodic_callback(gpointer data)
{
    /* Update devices */
    {
        /* Call into the backend and get the most up-to-date devices */
        get_devices(_module.devices, MAX_DEVICE_COUNT, &_module.deviceCount);
        GtkTreeIter iter;

        /* Get the first tree iterator and fill the tree with devices */
        int validIter = gtk_tree_model_get_iter_first(_module.deviceTreeModel, &iter);
        int i;
        for(i = 0; i < _module.deviceCount; ++i)
        {
            /* if the iterator isn't valid, append a new row to the list */
            if(!validIter) {
                gtk_list_store_append(_module.deviceListStore, &iter);
            }

            /* Initialize GValues to fill the list */
            GValue stringVal = G_VALUE_INIT;
            g_value_init(&stringVal, G_TYPE_STRING);
            GValue intVal = G_VALUE_INIT;
            g_value_init(&intVal, G_TYPE_INT);

            /* Set the values of the tree values */
            g_value_set_string(&stringVal, _module.devices[i].name);
            gtk_list_store_set_value(_module.deviceListStore, &iter, 0, &stringVal); // Device Name
            g_value_set_string(&stringVal, _module.devices[i].software_status);
            gtk_list_store_set_value(_module.deviceListStore, &iter, 1, &stringVal); // Device Software Status
            g_value_set_string(&stringVal, _module.devices[i].model);
            gtk_list_store_set_value(_module.deviceListStore, &iter, 2, &stringVal); // Device Model
            g_value_set_int(&intVal, _module.devices[i].id);
            gtk_list_store_set_value(_module.deviceListStore, &iter, 3, &intVal); // Device ID
            g_value_set_string(&stringVal, _module.devices[i].firmware_version);
            gtk_list_store_set_value(_module.deviceListStore, &iter, 4, &stringVal); // Device Firmware Version

            /* Go to the next list value */
            validIter = gtk_tree_model_iter_next(_module.deviceTreeModel, &iter);
        }
        /* Delete all the other list values, they don't exist on the network anymore */
        if(validIter) {
            while(gtk_list_store_remove(_module.deviceListStore, &iter)) ;
        }
    }
    return 1;
}

void application_close(void)
{
    /* Make sure we stop the backend thread */
    stop_backend();
    /* Call gtk's main quit function */
    gtk_main_quit();
}

int connect_all_signals(const char *ui_filename)
{
    GtkApplication *app;
    GtkBuilder *builder;
    GObject *obj;

    /* Parse UI file generated by glade */
    if((builder = gtk_builder_new_from_file(ui_filename)) == NULL)
    {
        /* If parse failed, it will return NULL, let user know */
        g_printerr("Error loading xml file: %s\n", ui_filename);
        return -1;
    }
    /* Start backend server */
    start_backend();

    /* Configure a 100ms periodic function */
    g_timeout_add(100, periodic_callback, NULL);

    /* Get every relevant object from the builder file */
    /* Connect X button to gtk_main_quit */
    obj = gtk_builder_get_object(builder, "window");
    g_signal_connect(obj, "destroy", G_CALLBACK(application_close), NULL);

    /* Connect run temporary server button to react function */
    obj = gtk_builder_get_object(builder, "btn_run_temporary_diag_server");
    g_signal_connect(obj, "clicked", G_CALLBACK(react_btn_run_temporary_diag_server), NULL);
    
    /* Connect address field to robot_controller file */
    obj = gtk_builder_get_object(builder, "txt_server_ip");
    g_signal_connect(obj, "changed", G_CALLBACK(react_server_ip_change), NULL);
    add_txt_server_ip_entry((GtkEntry *)obj);
    
    /* Connect port field to robot_controller file */
    obj = gtk_builder_get_object(builder, "txt_server_port");
    g_signal_connect(obj, "changed", G_CALLBACK(react_server_ip_change), NULL);
    add_txt_server_port_entry((GtkEntry *)obj);

    /* Connect status buffer to robot_controller file */
    obj = gtk_builder_get_object(builder, "txtbuf_robot_controller_status");
    add_txt_controller_status_buffer((GtkTextBuffer *)obj);

    /* Connect server address and port text change to react function */

    /* Get reference to the list store */
    _module.deviceListStore = (GtkListStore *)gtk_builder_get_object(builder, "lst_can_devices");
    _module.deviceTreeModel = (GtkTreeModel *)gtk_builder_get_object(builder, "lst_can_devices");
    

    return 0;
}
