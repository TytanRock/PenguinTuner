#include "robot_controller.h"
#include "app_callbacks.h"
#include "backend.h"
#include "can_devices.h"
#include "app_resources_ui.h"

#include <gtk/gtk.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_DEVICE_COUNT 30

static struct
{
    /* All the devices that are available from backend */
    can_device_t devices[MAX_DEVICE_COUNT];
    int deviceCount;

    double firm_upgrade_status;
    int firmware_upgrading;
    
    /* Gtk Widget references that matter */
    GtkTreeModel *deviceTreeModel;
    GtkLevelBar *firmUpgradeStatus;

    GtkTextBuffer *snapshotTxt;
}_module;

int count = 0;
gint periodic_callback(gpointer data)
{
    /* Update devices */
    /* Call into the backend and get the most up-to-date devices */
    if(get_devices(_module.devices, MAX_DEVICE_COUNT, &_module.deviceCount) == Ok)
    {
        GtkTreeIter iter;

        /* Get the first tree iterator and fill the tree with devices */
        int validIter = gtk_tree_model_get_iter_first(_module.deviceTreeModel, &iter);
        int i;
        for(i = 0; i < _module.deviceCount; ++i)
        {
            /* if the iterator isn't valid, append a new row to the list */
            if(!validIter) {
                gtk_list_store_append((GtkListStore *)_module.deviceTreeModel, &iter);
            }

            /* Initialize GValues to fill the list */
            GValue stringVal = G_VALUE_INIT;
            g_value_init(&stringVal, G_TYPE_STRING);
            GValue intVal = G_VALUE_INIT;
            g_value_init(&intVal, G_TYPE_INT);
            
            /* Set the values of the tree values */
            g_value_set_string(&stringVal, _module.devices[i].name);
            gtk_list_store_set_value((GtkListStore *)_module.deviceTreeModel, &iter, 0, &stringVal); // Device Name
            g_value_set_string(&stringVal, _module.devices[i].software_status);
            gtk_list_store_set_value((GtkListStore *)_module.deviceTreeModel, &iter, 1, &stringVal); // Device Software Status
            g_value_set_string(&stringVal, _module.devices[i].model);
            gtk_list_store_set_value((GtkListStore *)_module.deviceTreeModel, &iter, 2, &stringVal); // Device Model
            g_value_set_int(&intVal, _module.devices[i].id);
            gtk_list_store_set_value((GtkListStore *)_module.deviceTreeModel, &iter, 3, &intVal); // Device ID
            g_value_set_string(&stringVal, _module.devices[i].firmware_version);
            gtk_list_store_set_value((GtkListStore *)_module.deviceTreeModel, &iter, 4, &stringVal); // Device Firmware Version

            /* Go to the next list value */
            validIter = gtk_tree_model_iter_next(_module.deviceTreeModel, &iter);
        }
        /* Delete all the other list values, they don't exist on the network anymore */
        if(validIter) {
            while(gtk_list_store_remove((GtkListStore *)_module.deviceTreeModel, &iter)) ;
        }
        react_changed_device(NULL, NULL); // Update selected device to fix some issues
    }
    /* Update firmware status if we're upgrading */
    gtk_level_bar_set_value(_module.firmUpgradeStatus, _module.firmware_upgrading ? _module.firm_upgrade_status : 0);

    return 1;
}

void application_close(void)
{
    /* Make sure we stop the backend thread */
    stop_backend();
    /* Call gtk's main quit function */
    gtk_main_quit();
}

/**
 * This function gets called when backend has finished performing an action
 * This allows the form to get the response of an action
 */
void frontend_callback(backend_error err, const backend_action *action)
{
    switch(action->action)
    {
        case Set_ID:
        {
            if(err == Ok)
            {
                /* Update selected device to use newest ID */
                can_device_t dev = get_selected_device();
                dev.id = action->intParam;
                set_selected_device(dev);
            }
            break;
        }
        case Snapshot:
        {
            /* Get contents of string and copy it to module */
            if(err == Ok)
            {
                gtk_text_buffer_set_text(_module.snapshotTxt, *((char **)action->pointerParam), -1);
            }
            break;
        }
	case No_Action:
        case Set_Name:
	case Blink:
	case FactoryDefault:
	case Update_Firmware:
	case Get_Firm_status:
	    /* These actions don't do anything */
	    break;
    }
}

/**
 * This function is called during a firmware upgrade to update the frontend on the status of
 * the upgrade. When called, we should lock a mutex, update the firmware upgrade status variable,
 * and unlock, so that the periodic callback can pick up the new value
 */
void frontend_update_firm_status(double status, int stillUpgrading)
{
    _module.firmware_upgrading = stillUpgrading;
    _module.firm_upgrade_status = status;
}

int connect_all_signals()
{
    GtkBuilder *builder;
    GObject *obj;
    
    GBytes *resource = g_resource_lookup_data(app_resources_ui_get_resource(),
		                              "/ui/ui/MainApp.ui",
					      G_RESOURCE_LOOKUP_FLAGS_NONE,
					      NULL);
    const char *ui = (const char*)g_bytes_get_data(resource, NULL);
    
    /* Parse UI file generated by glade */
    if((builder = gtk_builder_new_from_string(ui, -1)) == NULL)
    {
        /* If parse failed, it will return NULL, let user know */
        g_printerr("Error loading xml file\n");
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
    
    /* Connect Selected Device label to can_devices file */
    obj = gtk_builder_get_object(builder, "txt_selected_device");
    add_lbl_selected_device((GtkLabel *)obj);
    
    /* Connect device stuff to can_devices file */
    obj = gtk_builder_get_object(builder, "btn_change_id");
    g_signal_connect(obj, "clicked", G_CALLBACK(react_changed_id), NULL);
    obj = gtk_builder_get_object(builder, "btn_update_devices");
    g_signal_connect(obj, "clicked", G_CALLBACK(react_update_firmware), NULL);
    obj = gtk_builder_get_object(builder, "btn_change_name");
    g_signal_connect(obj, "clicked", G_CALLBACK(react_changed_name), NULL);
    obj = gtk_builder_get_object(builder, "btn_blink");
    g_signal_connect(obj, "clicked", G_CALLBACK(react_blink_device), NULL);
    /* Connect objects from the self-test snapshot page */
    obj = gtk_builder_get_object(builder, "btn_blink_clear");
    g_signal_connect(obj, "clicked", G_CALLBACK(react_blink_device), NULL);
    obj = gtk_builder_get_object(builder, "btn_snapshot");
    g_signal_connect(obj, "clicked", G_CALLBACK(react_snapshot_device), NULL); 
    obj = gtk_builder_get_object(builder, "btn_factory_default");
    g_signal_connect(obj, "clicked", G_CALLBACK(react_default_device), NULL);
    
    obj = gtk_builder_get_object(builder, "txt_device_id");
    add_txt_change_id((GtkSpinButton *)obj);
    obj = gtk_builder_get_object(builder, "btn_choose_firmware");
    add_btn_firmware_file((GtkFileChooserButton *)obj);
    obj = gtk_builder_get_object(builder, "prg_firm_upgrade_status");
    _module.firmUpgradeStatus = (GtkLevelBar *)obj;
    obj = gtk_builder_get_object(builder, "txt_device_name");
    add_txt_device_name((GtkEntry *)obj);
    obj = gtk_builder_get_object(builder, "txt_device_selftest_snapshot");
    _module.snapshotTxt = (GtkTextBuffer *)obj;

    /* Connect server address and port text change to react function */

    /* Get reference to the list store */
    _module.deviceTreeModel = (GtkTreeModel *)gtk_builder_get_object(builder, "lst_can_devices");
    
    obj = gtk_builder_get_object(builder, "slct_device_selection");
    add_slct_device_selection((GtkTreeSelection *)obj);
    g_signal_connect(obj, "changed", G_CALLBACK(react_changed_device), NULL);

    return 0;
}
