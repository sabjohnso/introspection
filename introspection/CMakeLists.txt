configure_file(config.hpp.in config.hpp)

add_library(introspection_header INTERFACE)
set_target_properties(introspection_header PROPERTIES EXPORT_NAME header)
target_include_directories(introspection_header
  INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  $<INSTALL_INTERFACE:${introspection_INSTALL_INCLUDEDIR}>)

add_library(introspection::header ALIAS introspection_header)
  
install(TARGETS introspection_header
  EXPORT introspection_EXPORTS
  RUNTIME DESTINATION ${introspection_INSTALL_BINDIR}
  LIBRARY DESTINATION ${introspection_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${introspection_INSTALL_LIBDIR})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  DESTINATION ${introspection_INSTALL_INCLUDEDIR}/introspection)
