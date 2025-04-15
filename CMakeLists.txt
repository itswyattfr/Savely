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
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui Network UiTools Quick QuickControls2 QuickWidgets)

#=================== INCLUSION OF PROJECT FILES ===================#
set(FORMS_DIR "${CMAKE_SOURCE_DIR}/src/forms")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(QML_DIRECTORY "${CMAKE_SOURCE_DIR}/qml")
set(QML_RESOURCE_FILE "${CMAKE_BINARY_DIR}/qml_resources.qrc")

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

#======================== DYNAMIC QML LOADING ========================#
# Commenting out the QML resource embedding, so QML files are loaded at runtime
# qt_add_resources(QML_RESOURCES ${QML_RESOURCE_FILE})
# target_sources(Savely PRIVATE ${QML_RESOURCES})

target_include_directories(Savely PRIVATE ${FORMS_DIR})
target_include_directories(Savely PRIVATE ${INCLUDE_DIR})
target_include_directories(Savely PRIVATE ${SOURCE_DIR})
target_include_directories(Savely PRIVATE ${CMAKE_BINARY_DIR})

target_link_libraries(Savely PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    Qt6::Network
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::QuickWidgets
)

#======================== QML SCANNER ========================#
# Create qml directory if it doesn't exist
add_custom_command(
    TARGET Savely PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${QML_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${QML_DIRECTORY}"
        "$<TARGET_FILE_DIR:Savely>/qml"
    COMMENT "Copying QML files to the output directory"
)

# Copy QML folder again after build to ensure it's up to date
add_custom_command(
    TARGET Savely POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/qml"
        "$<TARGET_FILE_DIR:Savely>/qml"
    COMMENT "Copying QML folder to output directory"
)