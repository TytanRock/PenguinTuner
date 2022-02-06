#include "robot_controller.h"
#include "app_callbacks.h"
#include "backend.h"
#include "can_devices.h"

#include <stdio.h>

#define MAX_DEVICE_COUNT 30

static struct
{
    /* All the devices that are available from backend */
    can_device_t devices[MAX_DEVICE_COUNT];
    int deviceCount;

    double firm_upgrade_status;
    int firmware_upgrading;
    
    /* Gtk Widget references that matter */
    GtkListStore *deviceStore;
    GtkProgressBar *firmUpgradeStatus;

    GtkTextBuffer *snapshotTxt;

    GtkLabel *serverVersion;
    GtkLabel *serverStatus;
}_module;

//backend_error start_backend() {return 0;}
//backend_error stop_backend() {return 0;}
//
//backend_error set_ip(char *ipAddr) {return 0;}
//backend_error get_devices(can_device_t *devices, int maxDeviceCount, int *deviceCount) {return 0;}
//
//backend_error get_server_version(char *version) {return 0;}
//backend_error get_server_status(char *status) {return 0;}
//
//backend_error set_device_id(const can_device_t *device, int id, backend_callback callback) {return 0;}
//backend_error set_device_name(const can_device_t *device, const char *name, backend_callback callback) {return 0;}
//backend_error blink_device(const can_device_t *device, backend_callback callback) {return 0;}
//backend_error get_device_snapshot(const can_device_t *device, backend_callback callback) {return 0;}
//backend_error factory_default_device(const can_device_t *device, backend_callback callback) {return 0;}
//
//backend_error update_device_firmware(const can_device_t *device, const char *firmware_file, void (*firm_upgrade_callback)(double, int), backend_callback callback, upload_style style, const char *username, const char *password) {return 0;}


int count = 0;
gint periodic_callback(gpointer data)
{
    /* Update devices */
    /* Call into the backend and get the most up-to-date devices */
    if(get_devices(_module.devices, MAX_DEVICE_COUNT, &_module.deviceCount) == Ok)
    {
        GtkTreeIter iter;

        /* Get the first tree iterator and fill the tree with devices */
        int validIter = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(_module.deviceStore), &iter);
        int i;
        for(i = 0; i < _module.deviceCount; ++i)
        {
            /* if the iterator isn't valid, append a new row to the list */
            if(!validIter) {
                gtk_list_store_append(_module.deviceStore, &iter);
            }

            /* Initialize GValues to fill the list */
            GValue stringVal = G_VALUE_INIT;
            g_value_init(&stringVal, G_TYPE_STRING);
            GValue intVal = G_VALUE_INIT;
            g_value_init(&intVal, G_TYPE_INT);
            
            /* Set the values of the tree values */
            g_value_set_string(&stringVal, _module.devices[i].name);
            gtk_list_store_set_value(_module.deviceStore, &iter, 0, &stringVal); // Device Name
            g_value_set_string(&stringVal, _module.devices[i].software_status);
            gtk_list_store_set_value(_module.deviceStore, &iter, 1, &stringVal); // Device Software Status
            g_value_set_string(&stringVal, _module.devices[i].model);
            gtk_list_store_set_value(_module.deviceStore, &iter, 2, &stringVal); // Device Model
            g_value_set_int(&intVal, _module.devices[i].id);
            gtk_list_store_set_value(_module.deviceStore, &iter, 3, &intVal); // Device ID
            g_value_set_string(&stringVal, _module.devices[i].firmware_version);
            gtk_list_store_set_value(_module.deviceStore, &iter, 4, &stringVal); // Device Firmware Version

            /* Go to the next list value */
            validIter = gtk_tree_model_iter_next(GTK_TREE_MODEL(_module.deviceStore), &iter);
        }
        /* Delete all the other list values, they don't exist on the network anymore */
        if(validIter) {
            while(gtk_list_store_remove(_module.deviceStore, &iter)) ;
        }
        react_changed_device(NULL, NULL); // Update selected device to fix some issues
    }
    /* Update firmware status if we're upgrading */
    gtk_progress_bar_set_fraction(_module.firmUpgradeStatus, _module.firmware_upgrading ? _module.firm_upgrade_status : 0);

    /* If we're not field-upgrading, then check on the server status */
    if(_module.firmware_upgrading == 0)
    {
        /* Update Server Version and Status */
        char serverVers[50];
        get_server_version(serverVers);
        char fullVersion[100];
        sprintf(fullVersion, "Server Version:\n%s", serverVers);
        gtk_label_set_text(_module.serverVersion, fullVersion);

        char serverStatus[50];
        get_server_status(serverStatus);
        char fullStatus[100];
        sprintf(fullStatus, "Server Status:\n%s", serverStatus);
        gtk_label_set_text(_module.serverStatus, fullStatus);
    }

    return 1;
}

void application_close(void *data)
{
    /* Make sure we stop the backend thread */
    stop_backend();
}

/**
 * This function gets called when backend has finished performing an action
 * This allows the form to get the response of an action
 */
gboolean frontend_gui_callback(gpointer user_data)
{
    const backend_action *action = user_data;

    switch(action->action)
    {
        case Set_ID:
        {
            /* Update selected device to use newest ID */
            can_device_t dev = get_selected_device();
            dev.id = action->intParam;
            set_selected_device(dev);
            break;
        }
        case Snapshot:
        {
            /* Get contents of string and copy it to module */
            gtk_text_buffer_set_text(_module.snapshotTxt, *((char **)action->pointerParam), -1);
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
    return G_SOURCE_REMOVE;
}
void frontend_callback(backend_error err, const backend_action *action)
{
    if(err == Ok)
    {
        g_idle_add(frontend_gui_callback, (void *)action);
    }
}

/**
 * This function is called during a firmware upgrade to update the frontend on the status of
 * the upgrade. Just update the values by writing, we don't need to worry about read-modify-write conditions
 */
void frontend_update_firm_status(double status, int stillUpgrading)
{
    _module.firmware_upgrading = stillUpgrading;
    _module.firm_upgrade_status = status;
}

void add_progressbar_firm_upgrade_status(GtkProgressBar *firmUpgradeStatus) {
    _module.firmUpgradeStatus = firmUpgradeStatus;
}

void add_txt_self_test_snapshot(GtkTextBuffer *snapshotTxt) {
    _module.snapshotTxt = snapshotTxt;
}

void add_txt_server_version(GtkLabel *serverVersion) {
    _module.serverVersion = serverVersion;
}

void add_txt_server_status(GtkLabel *serverStatus) {
    _module.serverStatus = serverStatus;
}

void add_model_can_devices(GtkListStore *deviceListView) {
    _module.deviceStore = deviceListView;
}
