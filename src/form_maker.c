#include "form_maker.h"
#include "app_callbacks.h"
#include "robot_controller.h"
#include "can_devices.h"
#include <stdbool.h>

inline static void configure_widget_sizing(GtkWidget *widget, bool hExpand, bool vExpand, GtkAlign hAlign, GtkAlign vAlign) {
    gtk_widget_set_hexpand(widget, hExpand);
    gtk_widget_set_vexpand(widget, vExpand);
    gtk_widget_set_halign(widget, hAlign);
    gtk_widget_set_valign(widget, vAlign);
}

int create_form(GtkApplication *app, gpointer user_data)
{
    (void)user_data;
    /* Build the application from scratch */
    GtkWidget  *window;
    window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title((GTK_WINDOW(window)), "Penguin Tuner");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    /* Connect X button to gtk_main_quit */
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(application_close), app);

    /* Top level grid */
    GtkWidget *topGrid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), topGrid);
    configure_widget_sizing(topGrid, true, true, GTK_ALIGN_FILL, GTK_ALIGN_FILL);

    /* Menu bar for the application */
    /* First make the menu model */
    GMenu *menuModel = g_menu_new();
    GMenu *fileMenu = g_menu_new();
    GMenu *uploadStyle = g_menu_new();
    g_menu_append_submenu(menuModel, "File", G_MENU_MODEL(fileMenu));
    g_menu_append_submenu(fileMenu, "Upload Style", G_MENU_MODEL(uploadStyle));
    /* Make the stateful action for Post vs SSH uploads */
    GSimpleAction *uploadAction = g_simple_action_new_stateful("upload", G_VARIANT_TYPE_STRING, g_variant_new_string("POST"));
    GMenuItem *uploadPOST = g_menu_item_new("Post", "win.upload::POST");
    GMenuItem *uploadSSH = g_menu_item_new("SSH", "win.upload::SSH");
    g_signal_connect(uploadAction, "activate", G_CALLBACK(react_upload_change), window);
    g_action_map_add_action(G_ACTION_MAP(window), G_ACTION(uploadAction));
    g_menu_append_item(uploadStyle, uploadPOST);
    g_menu_append_item(uploadStyle, uploadSSH);
    /* Now make the menu bar with all the actions and submenus handled */
    GtkWidget *menuBar = gtk_popover_menu_bar_new_from_model(G_MENU_MODEL(menuModel));
    gtk_grid_attach(GTK_GRID(topGrid), menuBar, 0, 0, 3, 1);
    configure_widget_sizing(menuBar, true, false, GTK_ALIGN_FILL, GTK_ALIGN_START);
    gtk_widget_set_margin_start(menuBar, 10);
    gtk_widget_set_margin_end(menuBar, 10);

    /* Notebook that holds all the functions of PenguinTuner */
    GtkWidget *notebook = gtk_notebook_new();
    gtk_grid_attach(GTK_GRID(topGrid), notebook, 0, 1, 3, 1);
    configure_widget_sizing(notebook, true, true, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    gtk_widget_set_margin_top(notebook, 10);
    gtk_widget_set_margin_bottom(notebook, 10);
    gtk_widget_set_margin_start(notebook, 10);
    gtk_widget_set_margin_end(notebook, 10);


    /* Robot Controller Tab */
    GtkWidget *robotControllerTab = gtk_grid_new();
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), robotControllerTab, gtk_label_new("Robot Controller"));
    configure_widget_sizing(robotControllerTab, true, true, GTK_ALIGN_FILL, GTK_ALIGN_FILL);

    /* Robot Controller Description */
    GtkWidget *robotControllerDescription = gtk_text_view_new();
    GtkTextBuffer *robotControllerDescriptionBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(robotControllerDescription));
    gtk_text_buffer_set_text(robotControllerDescriptionBuffer, "This is Penguin Tuner", -1);
    gtk_grid_attach(GTK_GRID(robotControllerTab), robotControllerDescription, 0, 0, 4, 1);
    configure_widget_sizing(robotControllerDescription, true, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    gtk_widget_set_margin_top(robotControllerDescription, 10);
    gtk_widget_set_margin_bottom(robotControllerDescription, 10);
    gtk_widget_set_margin_start(robotControllerDescription, 10);
    gtk_widget_set_margin_end(robotControllerDescription, 10);
    gtk_widget_set_size_request(robotControllerDescription, -1, 70);

    /* Server Address Label */
    GtkWidget *serverAddressLabel = gtk_label_new("IP Address of Diagnostic Server");
    gtk_grid_attach(GTK_GRID(robotControllerTab), serverAddressLabel, 0, 1, 1, 1);
    configure_widget_sizing(serverAddressLabel, false, false, GTK_ALIGN_START, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_start(serverAddressLabel, 10);
    /* Server Address Entry */
    GtkWidget *serverAddressEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(robotControllerTab), serverAddressEntry, 0, 2, 1, 1);
    configure_widget_sizing(serverAddressEntry, true, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    GtkEntryBuffer *serverAddressEntryBuffer = gtk_entry_get_buffer(GTK_ENTRY(serverAddressEntry));
    gtk_entry_buffer_set_text(serverAddressEntryBuffer, "172.22.11.2", -1);
    g_signal_connect(G_OBJECT(serverAddressEntry), "changed", G_CALLBACK(react_server_ip_change), app);
    add_txt_server_ip_entry(GTK_ENTRY(serverAddressEntry));

    /* Server Port label */
    GtkWidget *serverPortLabel = gtk_label_new("Port of Diagnostic Server");
    gtk_grid_attach(GTK_GRID(robotControllerTab), serverPortLabel, 1, 1, 1, 1);
    configure_widget_sizing(serverPortLabel, false, false, GTK_ALIGN_START, GTK_ALIGN_CENTER);
    /* Server Port Entry */
    GtkWidget *serverPortEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(robotControllerTab), serverPortEntry, 1, 2, 1, 1);
    configure_widget_sizing(serverPortEntry, true, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    GtkEntryBuffer *serverPortEntryBuffer = gtk_entry_get_buffer(GTK_ENTRY(serverPortEntry));
    gtk_entry_buffer_set_text(serverPortEntryBuffer, "1250", -1);
    g_signal_connect(G_OBJECT(serverPortEntry), "changed", G_CALLBACK(react_server_ip_change), app);
    add_txt_server_port_entry(GTK_ENTRY(serverPortEntry));

    /* Run Diagnostic Server Button */
    GtkWidget *runDiagnosticServerButton = gtk_button_new_with_label("Run Diagnostic Server");
    gtk_grid_attach(GTK_GRID(robotControllerTab), runDiagnosticServerButton, 2, 2, 1, 1);
    configure_widget_sizing(runDiagnosticServerButton, true, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);

    /* Server status text field */
    GtkWidget *serverStatusTextField = gtk_text_view_new();
    GtkTextBuffer *serverStatusTextFieldBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(serverStatusTextField));
    gtk_text_buffer_set_text(serverStatusTextFieldBuffer, "Server Status", -1);
    configure_widget_sizing(serverStatusTextField, true, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    gtk_grid_attach(GTK_GRID(robotControllerTab), serverStatusTextField, 0, 3, 1, 1);
    gtk_widget_set_size_request(serverStatusTextField, -1, 70);
    gtk_widget_set_margin_top(serverStatusTextField, 10);
    gtk_widget_set_margin_bottom(serverStatusTextField, 10);
    gtk_widget_set_margin_start(serverStatusTextField, 10);
    gtk_widget_set_margin_end(serverStatusTextField, 10);
    add_txt_controller_status_buffer(serverStatusTextFieldBuffer);


    /* CAN Device List Tab */
    GtkWidget *canDeviceListTab = gtk_grid_new();
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), canDeviceListTab, gtk_label_new("CAN Device List"));
    configure_widget_sizing(canDeviceListTab, true, true, GTK_ALIGN_FILL, GTK_ALIGN_FILL);

    /* Create the tree model that displays the CAN devices */
    enum {
        DEVICE_NAME,
        SOFTWARE_STATUS,
        HARDWARE_NAME,
        ID,
        FIRMWARE_VERSION,
        N_COLUMNS,
    };
    /* CAN Device Tree View */
    GtkWidget *canDeviceTreeView = gtk_tree_view_new();
    gtk_grid_attach(GTK_GRID(canDeviceListTab), canDeviceTreeView, 0, 0, 6, 1);
    configure_widget_sizing(canDeviceTreeView, true, true, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    gtk_widget_set_size_request(canDeviceTreeView, -1, 100);
    gtk_tree_view_set_headers_clickable(GTK_TREE_VIEW(canDeviceTreeView), true);
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(canDeviceTreeView), true);
    gtk_tree_view_append_column(GTK_TREE_VIEW(canDeviceTreeView), gtk_tree_view_column_new_with_attributes("Device Name", gtk_cell_renderer_text_new(), "text", DEVICE_NAME, NULL));
    gtk_tree_view_append_column(GTK_TREE_VIEW(canDeviceTreeView), gtk_tree_view_column_new_with_attributes("Software Status", gtk_cell_renderer_text_new(), "text", SOFTWARE_STATUS, NULL));
    gtk_tree_view_append_column(GTK_TREE_VIEW(canDeviceTreeView), gtk_tree_view_column_new_with_attributes("Hardware", gtk_cell_renderer_text_new(), "text", HARDWARE_NAME, NULL));
    gtk_tree_view_append_column(GTK_TREE_VIEW(canDeviceTreeView), gtk_tree_view_column_new_with_attributes("ID", gtk_cell_renderer_text_new(), "text", ID, NULL));
    gtk_tree_view_append_column(GTK_TREE_VIEW(canDeviceTreeView), gtk_tree_view_column_new_with_attributes("Firmware Version", gtk_cell_renderer_text_new(), "text", FIRMWARE_VERSION, NULL));
    GtkListStore *canDeviceListStore = gtk_list_store_new(N_COLUMNS, 
                                                          G_TYPE_STRING, 
                                                          G_TYPE_STRING, 
                                                          G_TYPE_STRING, 
                                                          G_TYPE_INT, 
                                                          G_TYPE_STRING);
    gtk_tree_view_set_model(GTK_TREE_VIEW(canDeviceTreeView), GTK_TREE_MODEL(canDeviceListStore));
    add_model_can_devices(canDeviceListStore);
    add_slct_device_selection(GTK_TREE_SELECTION(gtk_tree_view_get_selection(GTK_TREE_VIEW(canDeviceTreeView))));
    

    /* Label for general device configuration */
    GtkWidget *deviceConfigurationLabel = gtk_label_new("General Device Configuration");
    gtk_grid_attach(GTK_GRID(canDeviceListTab), deviceConfigurationLabel, 0, 1, 3, 2);
    configure_widget_sizing(deviceConfigurationLabel, false, false, GTK_ALIGN_CENTER, GTK_ALIGN_CENTER);
    gtk_label_set_wrap(GTK_LABEL(deviceConfigurationLabel), true);

    /* Label for changing the device id */
    GtkWidget *deviceIdChangeLabel = gtk_label_new("Change the ID");
    gtk_grid_attach(GTK_GRID(canDeviceListTab), deviceIdChangeLabel, 0, 3, 1, 1);
    configure_widget_sizing(deviceIdChangeLabel, false, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    gtk_label_set_wrap(GTK_LABEL(deviceIdChangeLabel), true);
    /* Numeric to change the id */
    GtkWidget *deviceIdChangeNumeric = gtk_spin_button_new_with_range(0, 62, 1);
    gtk_grid_attach(GTK_GRID(canDeviceListTab), deviceIdChangeNumeric, 1, 3, 1, 1);
    configure_widget_sizing(deviceIdChangeNumeric, true, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    add_txt_change_id(GTK_SPIN_BUTTON(deviceIdChangeNumeric));
    /* Button to change the id */
    GtkWidget *deviceIdChangeButton = gtk_button_new_with_label("Change ID");
    gtk_grid_attach(GTK_GRID(canDeviceListTab), deviceIdChangeButton, 2, 3, 1, 1);
    configure_widget_sizing(deviceIdChangeButton, false, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    g_signal_connect(deviceIdChangeButton, "clicked", G_CALLBACK(react_changed_id), NULL);

    /* Label for changing the device name */
    GtkWidget *deviceNameChangeLabel = gtk_label_new("Change the Name");
    gtk_grid_attach(GTK_GRID(canDeviceListTab), deviceNameChangeLabel, 0, 4, 1, 1);
    configure_widget_sizing(deviceNameChangeLabel, false, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    gtk_label_set_wrap(GTK_LABEL(deviceNameChangeLabel), true);
    /* Text to change the name */
    GtkWidget *deviceNameChangeText = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(canDeviceListTab), deviceNameChangeText, 1, 4, 1, 1);
    configure_widget_sizing(deviceNameChangeText, true, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    add_txt_device_name(GTK_ENTRY(deviceNameChangeText));
    /* Button to change the name */
    GtkWidget *deviceNameChangeButton = gtk_button_new_with_label("Change Name");
    gtk_grid_attach(GTK_GRID(canDeviceListTab), deviceNameChangeButton, 2, 4, 1, 1);
    configure_widget_sizing(deviceNameChangeButton, false, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    g_signal_connect(deviceNameChangeButton, "clicked", G_CALLBACK(react_changed_name), NULL);

    /* Label that explains the button will animate LEDs of the selected device */
    GtkWidget *deviceLedAnimationLabel = gtk_label_new("Press to animate the LEDs of the selected device");
    gtk_grid_attach(GTK_GRID(canDeviceListTab), deviceLedAnimationLabel, 0, 5, 2, 1);
    configure_widget_sizing(deviceLedAnimationLabel, true, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    gtk_label_set_wrap(GTK_LABEL(deviceLedAnimationLabel), true);
    /* Button to animate LEDs */
    GtkWidget *deviceLedAnimationButton = gtk_button_new_with_label("Blink / Clear Faults");
    gtk_grid_attach(GTK_GRID(canDeviceListTab), deviceLedAnimationButton, 2, 5, 1, 1);
    configure_widget_sizing(deviceLedAnimationButton, false, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    g_signal_connect(deviceLedAnimationButton, "clicked", G_CALLBACK(react_blink_device), NULL);

    /* Label for Field-upgrading devices */
    GtkWidget *fieldUpgradeLabel = gtk_label_new("Field-upgrade Device Firmware");
    gtk_grid_attach(GTK_GRID(canDeviceListTab), fieldUpgradeLabel, 3, 1, 2, 1);
    configure_widget_sizing(fieldUpgradeLabel, false, false, GTK_ALIGN_CENTER, GTK_ALIGN_CENTER);
    /* Label to explain the File-Chooser box */
    GtkWidget *fieldUpgradeFileChooserLabel = gtk_label_new("Select the firmware file to be uploaded to device");
    gtk_grid_attach(GTK_GRID(canDeviceListTab), fieldUpgradeFileChooserLabel, 3, 2, 2, 1);
    configure_widget_sizing(fieldUpgradeFileChooserLabel, false, false, GTK_ALIGN_CENTER, GTK_ALIGN_CENTER);

    /* Text view with path to selected file */
    GtkWidget *fieldUpgradeFileChooserTextView = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(canDeviceListTab), fieldUpgradeFileChooserTextView, 3, 3, 1, 1);
    configure_widget_sizing(fieldUpgradeFileChooserTextView, true, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    add_txt_firmware_file(GTK_ENTRY(fieldUpgradeFileChooserTextView));
    /* Button to select file */
    GtkWidget *fieldUpgradeFileChooserButton = gtk_button_new_with_label("Select File");
    gtk_grid_attach(GTK_GRID(canDeviceListTab), fieldUpgradeFileChooserButton, 4, 3, 2, 1);
    configure_widget_sizing(fieldUpgradeFileChooserButton, false, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    g_signal_connect(fieldUpgradeFileChooserButton, "clicked", G_CALLBACK(react_update_firmware), NULL);

    /* Text view that explains the progress of the firmware upload */
    GtkWidget *fieldUpgradeStatusTextView = gtk_text_view_new();
    gtk_grid_attach(GTK_GRID(canDeviceListTab), fieldUpgradeStatusTextView, 3, 4, 1, 1);
    configure_widget_sizing(fieldUpgradeStatusTextView, true, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    /* Check box to update all devices of matching type */
    GtkWidget *fieldUpgradeFileChooserCheckBox = gtk_check_button_new();
    gtk_grid_attach(GTK_GRID(canDeviceListTab), fieldUpgradeFileChooserCheckBox, 4, 4, 1, 1);
    configure_widget_sizing(fieldUpgradeFileChooserCheckBox, false, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    /* Label to go along with checkbox */
    GtkWidget *updateAllDeviceCheckBoxLabel = gtk_label_new("Update all devices with matching type");
    gtk_grid_attach(GTK_GRID(canDeviceListTab), updateAllDeviceCheckBoxLabel, 5, 4, 1, 1);
    configure_widget_sizing(updateAllDeviceCheckBoxLabel, false, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    gtk_label_set_wrap(GTK_LABEL(updateAllDeviceCheckBoxLabel), true);

    /* Progress bar to indicate firmware upload progress */
    GtkWidget *fieldUpgradeProgressBar = gtk_progress_bar_new();
    gtk_grid_attach(GTK_GRID(canDeviceListTab), fieldUpgradeProgressBar, 3, 5, 1, 1);
    configure_widget_sizing(fieldUpgradeProgressBar, true, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    add_progressbar_firm_upgrade_status(GTK_PROGRESS_BAR(fieldUpgradeProgressBar));
    /* Button to update device firmware */
    GtkWidget *fieldUpgradeDeviceButton = gtk_button_new_with_label("Update Firmware");
    gtk_grid_attach(GTK_GRID(canDeviceListTab), fieldUpgradeDeviceButton, 4, 5, 2, 1);
    configure_widget_sizing(fieldUpgradeDeviceButton, false, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    g_signal_connect(fieldUpgradeDeviceButton, "clicked", G_CALLBACK(react_update_firmware), NULL);


    /* Self-test Snapshot tab */
    GtkWidget *selfTestSnapshotTab = gtk_grid_new();
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), selfTestSnapshotTab, gtk_label_new("Self-Test Snapshot"));

    /* Text view to display self-test snapshot */
    GtkWidget *selfTestScrollableWindow = gtk_scrolled_window_new();
    gtk_grid_attach(GTK_GRID(selfTestSnapshotTab), selfTestScrollableWindow, 0, 0, 3, 1);
    configure_widget_sizing(selfTestScrollableWindow, true, true, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    GtkWidget *selfTestSnapshotTextView = gtk_text_view_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(selfTestScrollableWindow), selfTestSnapshotTextView);
    add_txt_self_test_snapshot(gtk_text_view_get_buffer(GTK_TEXT_VIEW(selfTestSnapshotTextView)));

    /* Button to take the self-test snapshot */
    GtkWidget *selfTestSnapshotButton = gtk_button_new_with_label("Self-Test Snapshot");
    gtk_grid_attach(GTK_GRID(selfTestSnapshotTab), selfTestSnapshotButton, 0, 1, 1, 1);
    configure_widget_sizing(selfTestSnapshotButton, true, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    g_signal_connect(selfTestSnapshotButton, "clicked", G_CALLBACK(react_snapshot_device), NULL);

    /* Button to factory-default */
    GtkWidget *factoryDefaultButton = gtk_button_new_with_label("Factory Default");
    gtk_grid_attach(GTK_GRID(selfTestSnapshotTab), factoryDefaultButton, 1, 1, 1, 1);
    configure_widget_sizing(factoryDefaultButton, true, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    g_signal_connect(factoryDefaultButton, "clicked", G_CALLBACK(react_default_device), NULL);

    /* Button to blink/clear faults */
    GtkWidget *blinkAndClearFaultsButton = gtk_button_new_with_label("Blink / Clear Faults");
    gtk_grid_attach(GTK_GRID(selfTestSnapshotTab), blinkAndClearFaultsButton, 2, 1, 1, 1);
    configure_widget_sizing(blinkAndClearFaultsButton, true, false, GTK_ALIGN_FILL, GTK_ALIGN_FILL);
    g_signal_connect(blinkAndClearFaultsButton, "clicked", G_CALLBACK(react_blink_device), NULL);


    /* Server status stuff */
    GtkWidget *selectedDevice = gtk_label_new("No Device Selected");
    gtk_grid_attach(GTK_GRID(topGrid), selectedDevice, 0, 2, 1, 1);
    configure_widget_sizing(selectedDevice, true, false, GTK_ALIGN_CENTER, GTK_ALIGN_CENTER);
    add_lbl_selected_device(GTK_LABEL(selectedDevice));
    gtk_widget_set_size_request(selectedDevice, 20, 20);
    gtk_widget_set_margin_bottom(selectedDevice, 10);

    GtkWidget *serverStatus = gtk_label_new("Server Status: Not Connected");
    gtk_grid_attach(GTK_GRID(topGrid), serverStatus, 1, 2, 1, 1);
    configure_widget_sizing(serverStatus, true, false, GTK_ALIGN_CENTER, GTK_ALIGN_CENTER);
    add_txt_server_status(GTK_LABEL(serverStatus));
    gtk_widget_set_size_request(serverStatus, 20, 20);
    gtk_widget_set_margin_bottom(serverStatus, 10);

    GtkWidget *serverVersion = gtk_label_new("Server Version: Not Connected");
    gtk_grid_attach(GTK_GRID(topGrid), serverVersion, 2, 2, 1, 1);
    configure_widget_sizing(serverVersion, true, false, GTK_ALIGN_CENTER, GTK_ALIGN_CENTER);
    add_txt_server_version(GTK_LABEL(serverVersion));
    gtk_widget_set_size_request(serverVersion, 20, 20);
    gtk_widget_set_margin_bottom(serverVersion, 10);

    /* Non-GUI stuff */
    g_timeout_add(100, periodic_callback, NULL);

    /* Show the window now that everything's up */
    gtk_widget_show(window);
    return 0;
}

