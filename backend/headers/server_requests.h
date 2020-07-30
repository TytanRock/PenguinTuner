#ifndef __SERVER_REQUESTS_H__
#define __SERVER_REQUESTS_H__

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

typedef enum _backend_error
{
    Ok = 0,
    GeneralWarning = 1,
    GeneralError = -1,


    DeviceArrTooSmall = 2,

}backend_error;

/**
 * GetDevices
 * This function gets all devices from diagnostic server.
 * It will fill up to the specified amount with devices
 * Returns 0 if no error, nonzero otherwise
 */
backend_error get_devices(can_device_t *deviceArr, int maxDevices);

#endif

