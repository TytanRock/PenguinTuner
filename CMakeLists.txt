# Specify minimum required version of CMake
cmake_minimum_required (VERSION 2.8.11 )

# Project name
project (Linux_Tuner)

# Get all source files from the native/src directory, store it in SOURCES
aux_source_directory (native/src SOURCE_FILES)

# Specify include directory
include_directories (native/include INCLUDE_DIR)

# Add source files to executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_DIR})
