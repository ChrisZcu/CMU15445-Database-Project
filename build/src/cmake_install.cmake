# Install script for directory: /Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/binder/cmake_install.cmake")
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/buffer/cmake_install.cmake")
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/catalog/cmake_install.cmake")
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/common/cmake_install.cmake")
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/concurrency/cmake_install.cmake")
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/container/cmake_install.cmake")
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/execution/cmake_install.cmake")
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/recovery/cmake_install.cmake")
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/storage/cmake_install.cmake")
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/type/cmake_install.cmake")
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/planner/cmake_install.cmake")
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/primer/cmake_install.cmake")
  include("/Users/teechris/Desktop/SUSTech/CMU15445Project/CMU15445-Database-Project/build/src/optimizer/cmake_install.cmake")

endif()

