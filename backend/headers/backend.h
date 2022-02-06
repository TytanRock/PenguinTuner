#ifndef __BACKEND_H__
#define __BACKEND_H__

#define MAX_SIZE_COUNT 30

#include "penguinbackend_export.h"

typedef enum _backend_error
{
    /* General warnings and errors */
    Ok = 0,
    GeneralWarning = 1,
    GeneralError = -1,

    /* Warnings & Errors related to CAN devices */
    DeviceArrTooSmall = 10,
    
    /* Warnings & Errors related to the backend */
    BackendThreadStarted = -100,
    BackendThreadNotStarted = -101,
    BackendBusy = -102,
    ActionAlreadyOccurring = -103,
    FilenameEmpty = -104,

    /* Warnings and Errors related to Diagnostic Server */
    InvalidServerResponse = -200,
    FactoryUpgradeTimedOut = -201,

    /* Warnings and Error related to connection style */
    NoSSHUsername = -300,
    FailedSshCreate = -301,
    SSHAuthFailure = -302,
    FailedSshChannelCreate = -303,
    FailedCreateDir = -304,
    FailedSshScpCreate = -305,
    SCPNoInit = -306,
    SCPCannotPushFile = -307,
    NoSCPWrite = -308
}backend_error;

typedef enum _action_type
{
    No_Action,
    Set_ID,
    Set_Name,
    Blink,
    Snapshot,
    FactoryDefault,
    Update_Firmware,
    Get_Firm_status,
}action_type;

typedef enum _upload_style
{
    POST,
    SSH
}upload_style;

/**
 * This is what will be passed between application and backend
 * to decide what device to interact with, and to display
 */
typedef struct _can_device_t
{
    char name[50];
    char software_status[50];
    char model[50];
    int id;
    char firmware_version[20];
}can_device_t;

struct _backend_action;

typedef void (*backend_callback)(backend_error, const struct _backend_action *);

typedef struct _backend_action
{
    action_type action;
    const can_device_t *device;
    
    int intParam;
    void (*functionParam)(double,int);
    void *pointerParam;
    char stringParam[100];

    backend_callback callback;

    unsigned requested : 1;
}backend_action;


PENGUINBACKEND_EXPORT backend_error start_backend();
PENGUINBACKEND_EXPORT backend_error stop_backend();

PENGUINBACKEND_EXPORT backend_error set_ip(char *ipAddr);
PENGUINBACKEND_EXPORT backend_error get_devices(can_device_t *devices, int maxDeviceCount, int *deviceCount);

PENGUINBACKEND_EXPORT backend_error get_server_version(char *version);
PENGUINBACKEND_EXPORT backend_error get_server_status(char *status);

PENGUINBACKEND_EXPORT backend_error set_device_id(const can_device_t *device, int id, backend_callback callback);
PENGUINBACKEND_EXPORT backend_error set_device_name(const can_device_t *device, const char *name, backend_callback callback);
PENGUINBACKEND_EXPORT backend_error blink_device(const can_device_t *device, backend_callback callback);
PENGUINBACKEND_EXPORT backend_error get_device_snapshot(const can_device_t *device, backend_callback callback);
PENGUINBACKEND_EXPORT backend_error factory_default_device(const can_device_t *device, backend_callback callback);

PENGUINBACKEND_EXPORT backend_error update_device_firmware(const can_device_t *device, const char *firmware_file, void (*firm_upgrade_callback)(double, int), backend_callback callback, upload_style style, const char *username, const char *password);

#endif

