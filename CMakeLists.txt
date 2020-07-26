# Specify minimum required version of CMake
cmake_minimum_required (VERSION 2.8.11 )

# Project name
project (LinuxTuner C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

# Get all source files from the native/src directory, store it in SOURCES
aux_source_directory (native/src SOURCE_FILES)

# Specify include directory
include_directories (native/include INCLUDE_DIR)

# Add source files to executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES})
