//
// ... Standard header filesa
//
#include <iostream>

//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... introspection header files
//
#include <introspection/introspection.hpp>

namespace introspection::testing {

   enum class thing : char { one, two };

   enum class a { b, c };
   TEST(enumdata, type_name) {
      ASSERT_EQ(
        type_name<thing>,
        std::string_view("introspection::testing::thing"));
   }

   TEST(enumdata, unqualified_type_name) {
      ASSERT_EQ(unqualified_type_name<thing>, std::string_view("thing"));
   }

   TEST(enumdata, enum_value_name) {
      ASSERT_EQ(
        enum_value_name<thing::one>,
        std::string_view("introspection::testing::thing::one"));
   }

   TEST(enumdata, unqualified_enum_name) {
      ASSERT_EQ(
        unqualified_enum_value_name<thing::one>,
        std::string_view("one"));
   }

   TEST(enumdata, type_qualified_enum_value_name) {
      ASSERT_EQ(
        type_qualified_enum_value_name<thing::one>,
        std::string_view("thing::one"));
   }

   TEST(enumdata, type_qualified_enum_value_name_alternate) {
      ASSERT_EQ(type_qualified_enum_value_name<a::b>, std::string_view("a::b"));
   }

} // end of namespace introspection::testing
