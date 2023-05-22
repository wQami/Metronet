cmake_minimum_required(VERSION 3.6)
project(Metronet)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-std=c++98 -Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)

# Set Library dir
link_directories(gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES metronetTests.cpp Station.cpp Station.h Tram.cpp Tram.h MetronetMain.cpp DesignByContract.h tinyxml/tinyxml.h tinyxml/tinyxml.cpp tinyxml/tinystr.h tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp Metronet.cpp Metronet.h MetronetParser.cpp MetronetParser.h Spoor.cpp Spoor.h MetronetOutput.cpp MetronetOutput.h MetronetSimulation.cpp MetronetSimulation.h)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES metronetTests.cpp Station.cpp Station.h Tram.cpp Tram.h DesignByContract.h tinyxml/tinyxml.h tinyxml/tinyxml.cpp tinyxml/tinystr.h tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp Metronet.cpp Metronet.h MetronetParser.cpp MetronetParser.h Spoor.cpp Spoor.h MetronetOutput.cpp MetronetOutput.h MetronetSimulation.cpp MetronetSimulation.h)

# Create RELEASE target
add_executable(main ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(testing ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(testing gtest)