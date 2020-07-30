# Specify minimum required version of CMake
cmake_minimum_required (VERSION 2.8.11 )

# Project name
project (PenguinTuner C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

# Get all source files from the native/src directory, store it in SOURCES
aux_source_directory (native/src SOURCE_FILES)

# Specify include directory
include_directories (native/include INCLUDE_DIR)
include_directories (backend/headers INCLUDE_DIR)
link_directories (backend/lib)

# Add source files to executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_DIR})
# Copy config files for styling the widgets
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/config/ $<TARGET_FILE_DIR:${PROJECT_NAME}>)
target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES})
