configure_file(config.hpp.in config.hpp)

add_library(instrospection INTERFACE)
target_include_directories(instrospection
  INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  $<INSTALL_INTERFACE:${instrospection_INSTALL_INCLUDEDIR}>)

add_library(instrospection::instrospection ALIAS instrospection)
  
install(TARGETS instrospection
  EXPORT instrospection_EXPORTS
  RUNTIME DESTINATION ${instrospection_INSTALL_BINDIR}
  LIBRARY DESTINATION ${instrospection_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${instrospection_INSTALL_LIBDIR})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  DESTINATION ${instrospection_INSTALL_INCLUDEDIR})
