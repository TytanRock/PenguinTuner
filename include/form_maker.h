#ifndef __PENGUINTUNER_FORM_MAKER_H
#define __PENGUINTUNER_FORM_MAKER_H

#include <gtk/gtk.h>

/**
 * Connect all signals from the UI xml file specified
 * Returns: 0 if success, nonzero otherwise
 */
int create_form(GtkApplication *app, gpointer user_data);

#endif //__PENGUINTUNER_FORM_MAKER_H
