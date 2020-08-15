# Penguin Tuner

This is a cross-platform GUI application designed to be used similarly to CTRE's Phoenix Tuner, which interacts with CTRE's diagnostic server to perform actions on CTRE CAN bus devices.

This was made and is maintained by Cory Ness, an employee of CTRE. This is not supported by CTRE, any support questions/feature requests regarding Penguin Tuner should be made in this repository's issue tracker.

Due to licensing concerns, only the GUI application will be open-sourced.
The backend of this application, the stuff that deals with communicating to diagnostic server, will be provided via a shared-object and linked into the application.
This allows CTRE to maintain proprietery licensing of the backend while still providing everything the community needs to use Phoenix and CTRE CAN devices in a variety of scenarios.

## Phoenix-Linux-SocketCAN-Example Submodule

This repository is added as a submodule in order to not only provide an example of using phoenix in a linux environment, but also as a means of instantiating a diagnostic server for means of testing this applciation.
Testing this application using the provided submodule is done by the following:
 1. Comment line 51 of example.cpp `c_SetPhoenixDiagnosticsStartTime(-1);`. This allows diagnostic server to run when executing the example application.
 2. Comment everything inside the `while (true)` statement from line 56. We don't need any of this, just an infinite while loop for the diagnostic server to run.
 3. Add a `sleepApp(100)` to the end of the now empty while loop. This prevents resources from being sucked up by the application, and 100ms is suitable to react to any keyboard interrupts.
