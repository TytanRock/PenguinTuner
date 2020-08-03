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


/**
 * This is what will be passed between application and backend
 * to decide what device to interact with, and to display
 */
typedef struct _can_device_t
{
    char name[20];
    char software_status[40];
    char model[20];
    int id;
    char firmware_version[10];
}can_device_t;

backend_error start_backend();
backend_error stop_backend();

backend_error get_devices(can_device_t *devices, int maxDeviceCount, int *deviceCount);

#endif

