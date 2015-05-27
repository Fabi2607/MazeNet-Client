cmake_minimum_required(VERSION 2.8)
set(PROJECT_NAME "MazeNet-Client")

project ( ${PROJECT_NAME} )

#set version variables
set (PROJECT_MAJOR_VERSION 0)
set (PROJECT_MINOR_VERSION 1)
set (CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required

#set Compiler Flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Weffc++ -pedantic -lpthread")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -g -O0")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

#linker
set(CMAKE_LD_FLAGS "${CMAKE_LD_FLAGS}")

add_definitions(-DBOOST_LOG_DYN_LINK)

# set custom modul path
set(CMAKE_MODULE_PATH "${MazeNet-Client_SOURCE_DIR}/scripts/cmake/")
message(STATUS "Module Path: " ${CMAKE_MODULE_PATH})

#determine bitness
set(bitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(bitness 64)
endif()

execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} --version
    COMMAND head -n1
    WORKING_DIRECTORY ${MazeNet-Client_SOURCE_DIR}
    OUTPUT_VARIABLE COMPILER_VERSION)
string(STRIP ${COMPILER_VERSION} COMPILER_VERSION)

execute_process(
    COMMAND git rev-list HEAD --count
    WORKING_DIRECTORY ${MazeNet-Client_SOURCE_DIR}
    OUTPUT_VARIABLE REVISION_NUMBER)
string(STRIP ${REVISION_NUMBER} REVISION_NUMBER)

string(STRIP ${PROJECT_MAJOR_VERSION} PROJECT_MAJOR_VERSION)
string(STRIP ${PROJECT_MINOR_VERSION} PROJECT_MINOR_VERSION)

message(STATUS ${PROJECT_MAJOR_VERSION} ${PROJECT_MINOR_VERSION})

configure_file (
  "${MazeNet-Client_SOURCE_DIR}/src/util/cfg/Config.hpp.in"
  "${MazeNet-Client_SOURCE_DIR}/src/util/cfg/Config.hpp"
  )


include(FindPkgConfig)

include_directories ("${PROJECT_SOURCE_DIR}/src")

find_package( Boost 1.55.0 COMPONENTS system thread chrono log log_setup program_options filesystem REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )

# find ICU for boost unicode support
find_package(ICU REQUIRED)

#add executable
add_executable ( ${PROJECT_NAME} src/main.cpp )

message(STATUS "------------------------------")
message(STATUS "entering subdirectories")

# add subdirs
add_subdirectory ( src )
include_directories ( src )

message(STATUS "------------------------------")
message(STATUS "linking internal libraries")


message(STATUS "linking util library")
target_link_libraries ( ${PROJECT_NAME} util)

message(STATUS "linking cfg library")
target_link_libraries ( ${PROJECT_NAME} cfg)

message(STATUS "linking logging library")
target_link_libraries ( ${PROJECT_NAME} logging)

message(STATUS "------------------------------")
message(STATUS "linking external libraries")

message(STATUS "linking Boost: " ${Boost_LIBRARIES})
target_link_libraries ( ${PROJECT_NAME} ${Boost_LIBRARIES})

message(STATUS "linking ICU: " ${ICU_LIBRARIES})
target_link_libraries ( ${PROJECT_NAME} ${ICU_LIBRARIES} )

message(STATUS "------------------------------")

message(STATUS "DONE!")
