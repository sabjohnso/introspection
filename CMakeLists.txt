cmake_minimum_required(VERSION 3.12)

project(introspection VERSION 1.1.0 LANGUAGES CXX)

if(PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  option(introspection_BUILD_TESTING "Build the introspection tests" ON)
endif()
option(introspection_INSTALL_WITH_VERSION "Instrall introspection in a version specific directory" OFF)
set(introspection_CXX_STANDARD 20 CACHE STRING "C++ standard for introspection")

include(GNUInstallDirs)

set(introspection_INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR})
set(introspection_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
set(introspection_INSTALL_CONFDIR ${introspection_INSTALL_LIBDIR}/cmake/introspection-${PROJECT_VERSION})

if(introspection_INSTALL_WITH_VERSION)
  set(introspection_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR}/introspection-${PROJECT_VERSION})
else()
  set(introspection_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR})
endif()

list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/cmake)
include(introspection_deps)

add_subdirectory(introspection)

if(introspection_BUILD_TESTING)
  include(CTest)
  if(BUILD_TESTING)
    add_subdirectory(introspection_testing)
  endif()
endif()

install(EXPORT introspection_EXPORTS
  NAMESPACE introspection::
  FILE introspection-exports.cmake
  DESTINATION ${introspection_INSTALL_CONFDIR})

configure_file(introspection-config.cmake.in introspection-config.cmake)
install(FILES ${PROJECT_BINARY_DIR}/introspection-config.cmake
  DESTINATION ${introspection_INSTALL_CONFDIR})
