cmake_minimum_required(VERSION 3.15)

if (WIN32)
    project(Savely LANGUAGES CXX)
elseif(UNIX)
    project(Savely)
endif()

set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo;Debug" CACHE STRING "" FORCE)

#======================== INCLUSION OF QT ========================#
list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.9.0/msvc2022_64/lib/cmake")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_BUILD_TYPE "Release")
find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)
find_package(Qt6Network REQUIRED)  # Added Network module

#=================== INCLUSION OF PROJECT FILES ===================#
set(FORMS_DIR "${CMAKE_SOURCE_DIR}/src/forms")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${FORMS_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

set(CRITICAL_SOURCES
    "${SOURCE_DIR}/main.cpp"
    "${SOURCE_DIR}/mainwindow.cpp"
    "${INCLUDE_DIR}/mainwindow.h"
)

foreach(file ${CRITICAL_SOURCES})
    if(NOT EXISTS "${file}")
        message(FATAL_ERROR "Critical file not found: ${file}")
    endif()
endforeach()

file(GLOB_RECURSE ADDITIONAL_SOURCES
    "${FORMS_DIR}/*.ui"
    "${FORMS_DIR}/*.qrc"
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
)

set(SOURCES ${CRITICAL_SOURCES} ${ADDITIONAL_SOURCES})

list(REMOVE_DUPLICATES SOURCES)

#======================== SETUP EXECUTABLE ========================#
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:RELWITHDEBINFO>:QT_MESSAGELOGCONTEXT>
)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})

if (WIN32) 
    add_executable(Savely WIN32 ${SOURCES})
elseif(UNIX)
    add_executable(Savely ${SOURCES})
endif()

target_include_directories(Savely PRIVATE ${FORMS_DIR})
target_include_directories(Savely PRIVATE ${INCLUDE_DIR})
target_include_directories(Savely PRIVATE ${SOURCE_DIR})

#===================== LINKING LIBRARIES =======================#
target_link_libraries(Savely Qt6::Widgets Qt6::Network)  # Added Network library