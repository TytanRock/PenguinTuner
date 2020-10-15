# Specify minimum required version of CMake
cmake_minimum_required (VERSION 3.0 )

file(READ "version.txt" ver)
string(REGEX MATCH "VERSION_MAJOR ([0-9]*)" _ ${ver})
set(major ${CMAKE_MATCH_1})
string(REGEX MATCH "VERSION_MINOR ([0-9]*)" _ ${ver})
set(minor ${CMAKE_MATCH_1})
string(REGEX MATCH "VERSION_PATCH ([0-9]*)" _ ${ver})
set(patch ${CMAKE_MATCH_1})

# Project name
project (PenguinTuner LANGUAGES C VERSION "${major}.${minor}.${patch}")


message("version: ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

find_package(PkgConfig REQUIRED)
find_package(CURL REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})

add_library(Penguin_Backend SHARED IMPORTED)
set_property(TARGET Penguin_Backend PROPERTY IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/backend/lib/libPenguin_Backend.so")

add_definitions(${GTK3_CFLAGS_OTHER})

# Get all source files from the native/src directory, store it in SOURCES
aux_source_directory (native/src SOURCE_FILES)

# Specify include directory
include_directories (native/include INCLUDE_DIR)
include_directories (backend/headers INCLUDE_DIR)

# Creates C resources file from files in given directory
function(create_resources dir output)
    # Create empty output file
    file(WRITE ${output} "")
    # Collect input files
    file(GLOB bins ${dir}/*)
    # Iterate through input files
    foreach(bin ${bins})
        # Get short filename
        string(REGEX MATCH "([^/]+)$" filename ${bin})
        # Replace filename spaces & extension separator for C compatibility
        string(REGEX REPLACE "\\.| |-" "_" filename ${filename})
        # Read hex data from file
        file(READ ${bin} filedata HEX)
        # Convert hex data for C compatibility
        string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," filedata ${filedata})
        # Append data to output file
        file(APPEND ${output} "const unsigned char ${filename}[] = {${filedata}};\nconst unsigned ${filename}_size = sizeof(${filename});\n")
    endforeach()
endfunction()

create_resources(${CMAKE_SOURCE_DIR}/config ${CMAKE_CURRENT_BINARY_DIR}/resources.c)

# Add source files to executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${CMAKE_CURRENT_BINARY_DIR}/resources.c ${INCLUDE_DIR})

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND cp ${CMAKE_SOURCE_DIR}/config/MainApp.ui .)
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ld -r -b binary MainApp.ui -o ${CMAKE_CURRENT_BINARY_DIR}/MainApp.o)

# Copy config files for styling the widgets
target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES})
target_link_libraries(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/backend/lib/libPenguin_Backend.so")
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})

install(TARGETS PenguinTuner
    DESTINATION bin
)
install(FILES "${CMAKE_SOURCE_DIR}/backend/lib/libPenguin_Backend.so"
    DESTINATION lib
)

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "TytanRock")
include(CPack)

