//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... introspection header files
//
#include <introspection/introspection.hpp>

namespace introspection::testing {

   struct Example {};

   template<typename... Ts>
   struct Example_template {};

   TEST(type_name, fundamental_type) {
      ASSERT_EQ(type_name<int>, std::string_view("int"));
      ASSERT_EQ(unqualified_type_name<int>, std::string_view("int"));
      ASSERT_EQ(unspecialized_type_name<int>, std::string_view("int"));
      ASSERT_EQ(bare_type_name<int>, std::string_view("int"));
   }

   TEST(type_name, qualified_type) {
      ASSERT_EQ(
        type_name<Example>,
        std::string_view("introspection::testing::Example"));
      ASSERT_EQ(unqualified_type_name<Example>, std::string_view("Example"));
      ASSERT_EQ(
        unspecialized_type_name<Example>,
        std::string_view("introspection::testing::Example"));
      ASSERT_EQ(bare_type_name<Example>, std::string_view("Example"));
   }

   TEST(type_name, qualified_type_template) {
      ASSERT_EQ(
        type_name<Example_template<Example>>,
        std::string_view("introspection::testing::Example_template<"
                         "introspection::testing::Example>"));
      ASSERT_EQ(
        unqualified_type_name<Example_template<Example>>,
        std::string_view("Example_template<introspection::testing::Example>"));
      ASSERT_EQ(
        unspecialized_type_name<Example_template<Example>>,
        std::string_view("introspection::testing::Example_template"));
      ASSERT_EQ(
        bare_type_name<Example_template<Example>>,
        std::string_view("Example_template"));
   }

} // namespace introspection::testing
