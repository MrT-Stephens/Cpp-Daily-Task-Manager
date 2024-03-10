cmake_minimum_required(VERSION 3.9.6...3.15.0)
project(EmptyStarter LANGUAGES C CXX)

set(ELEMENTS_ROOT "${PROJECT_SOURCE_DIR}/lib/elements")

if (NOT ELEMENTS_ROOT)
   message(FATAL_ERROR "ELEMENTS_ROOT is not set")
endif()

# Make sure ELEMENTS_ROOT is an absolute path to add to the CMake module path
get_filename_component(ELEMENTS_ROOT "${ELEMENTS_ROOT}" ABSOLUTE)
set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${ELEMENTS_ROOT}/cmake")

# If we are building outside the project, you need to set ELEMENTS_ROOT:
if (NOT ELEMENTS_BUILD_EXAMPLES)
   include(ElementsConfigCommon)
   set(ELEMENTS_BUILD_EXAMPLES OFF)
   add_subdirectory(${ELEMENTS_ROOT} elements)
endif()

set(ELEMENTS_APP_PROJECT "Daily-Task-Manager")
set(ELEMENTS_APP_TITLE "Daily Task Manager")
set(ELEMENTS_APP_COPYRIGHT "Copyright (c) 2016-2023 Thomas Stephens")
set(ELEMENTS_APP_ID "com.MrT-Stephens.Daily-Task-Manager")
set(ELEMENTS_APP_VERSION "1.0")

set(ELEMENTS_APP_SOURCES 
	"${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Header Files/NoCopy.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Header Files/Vector.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Header Files/Algorithm.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Header Files/Xml.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Header Files/View.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Header Files/Controller.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Header Files/Observer.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Header Files/Subject.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Header Files/Task.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Header Files/TaskManager.h"

	"${CMAKE_CURRENT_SOURCE_DIR}/Source Files/Xml.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source Files/View.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source Files/Controller.cpp"
)

# For your custom application icon on macOS or Windows see cmake/AppIcon.cmake module
include(AppIcon)
include(ElementsConfigApp)
