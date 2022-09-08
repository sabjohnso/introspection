find_package(GTest)

macro(introspection_add_test test_name exe_name)
  add_executable(${exe_name} ${ARGN})
  target_link_libraries(${exe_name} PRIVATE
    introspection::header
    GTest::gtest_main)
  set_target_properties(${exe_name}
    PROPERTIES
    CXX_STANDARD ${introspection_CXX_STANDARD})
  add_test(${test_name} ${exe_name})
endmacro()

introspection_add_test(macros macros_test macros_test.cpp)
introspection_add_test(metadata metadata_test metadata_test.cpp)
introspection_add_test(type_name type_name_test type_name_test.cpp)
introspection_add_test(enumdata enumdata_test enumdata_test.cpp)
