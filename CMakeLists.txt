cmake_minimum_required(VERSION 3.10)
project(penguintuner C)

# Find required packages
find_package(Threads REQUIRED)
find_package(libssh REQUIRED)
find_package(CURL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# Configure source files
SET(SRCS src/app_callbacks.c
         src/application.c
         src/can_devices.c
         src/robot_controller.c
         src/form_maker.c)

# Configure project
add_executable(${PROJECT_NAME} ${SRCS})

target_link_directories(${PROJECT_NAME} PRIVATE ${GTK4_LIBRARY_DIRS})
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/backend/lib/win64)

# Target link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
target_link_libraries(${PROJECT_NAME} PRIVATE ssh)
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTK4_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE penguinbackend)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/backend/headers)
target_include_directories(${PROJECT_NAME} PRIVATE ${GTK4_INCLUDE_DIRS})

# Copy libs in case they're necessary
add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/backend/lib/win64 ${CMAKE_BINARY_DIR}/Debug
    COMMENT "Copying necessary libraries into build output"
)
