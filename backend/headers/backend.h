#ifndef __BACKEND_H__
#define __BACKEND_H__

#define MAX_SIZE_COUNT 30

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
}backend_error;

typedef enum _action_type
{
    No_Action,
    Set_ID,
    Update_Firmware,
    Get_Firm_status,
}action_type;

/**
 * This is what will be passed between application and backend
 * to decide what device to interact with, and to display
 */
typedef struct _can_device_t
{
    char name[50];
    char software_status[40];
    char model[20];
    int id;
    char firmware_version[10];
}can_device_t;

struct _backend_action;

typedef void (*backend_callback)(backend_error, const struct _backend_action *);

typedef struct _backend_action
{
    action_type action;
    const can_device_t *device;
    
    int intParam;
    const void *pointerParam;

    backend_callback callback;

    unsigned requested : 1;
}backend_action;


backend_error start_backend();
backend_error stop_backend();

backend_error set_ip(char *ipAddr);
backend_error get_devices(can_device_t *devices, int maxDeviceCount, int *deviceCount);

backend_error set_device_id(const can_device_t *device, int id, backend_callback callback);
backend_error update_device_id(const can_device_t *device, char *firmware_file, backend_callback callback);

#endif

