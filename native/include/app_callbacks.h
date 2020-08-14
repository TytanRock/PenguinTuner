#ifndef __APP_CALLBACKS_H__
#define __APP_CALLBACKS_H__

#include "backend.h"

/**
 * Connect all signals from the UI xml file specified
 * Returns: 0 if success, nonzero otherwise
 */
int connect_all_signals(const char *ui_filename);

void frontend_callback(backend_error err, const backend_action *action);
void frontend_update_firm_status(double status, int stillUpgrading);

#endif
