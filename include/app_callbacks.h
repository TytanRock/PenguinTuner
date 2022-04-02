#ifndef __APP_CALLBACKS_H__
#define __APP_CALLBACKS_H__

#include "backend.h"
#include <gtk/gtk.h>

void frontend_callback(backend_error err, const backend_action *action);
void frontend_update_firm_status(double status, int stillUpgrading);
void application_close(void *data);
void add_txt_self_test_snapshot(GtkTextBuffer *snapshotTxt);
gint periodic_callback(gpointer data);

void add_progressbar_firm_upgrade_status(GtkProgressBar *firmUpgradeStatus);
void add_txt_server_version(GtkLabel *serverVersion);
void add_txt_server_status(GtkLabel *serverStatus);
void add_model_can_devices(GtkListStore *deviceListView);

#endif
