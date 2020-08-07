cmake_minimum_required(VERSION 3.12)

project(instrospection VERSION 0.1.0 LANGUAGES C CXX)

option(instrospection_BUILD_TESTING "Build the instrospection tests" ON)

include(GNUInstallDirs)
set(instrospection_INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR})
set(instrospection_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
set(instrospection_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR})
set(instrospection_INSTALL_CONFDIR ${instrospection_INSTALL_LIBDIR}/cmake/instrospection-${PROJECT_VERSION})

list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/cmake)
include(instrospection_deps)

add_subdirectory(instrospection)

if(instrospection_BUILD_TESTING)
  include(CTest)
  if(BUILD_TESTING)
    add_subdirectory(instrospection_testing)
  endif()
endif()

install(EXPORT instrospection_EXPORTS
  NAMESPACE instrospection::
  FILE instrospection-exports.cmake
  DESTINATION ${instrospection_INSTALL_CONFDIR})

configure_file(instrospection-config.cmake.in instrospection-config.cmake)
install(FILES ${PROJECT_BINARY_DIR}/instrospection-config.cmake
  DESTINATION ${instrospection_INSTALL_CONFDIR})








