//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... introspection header files
//
#include <introspection/introspection.hpp>
#include <introspection/macros.hpp>

#define QUOTE_AUX(...) #__VA_ARGS__
#define QUOTE(...) QUOTE_AUX(__VA_ARGS__)

namespace introspection::testing {

   struct Thing {
      std::array<int, 2> member1{};
      int member2{};
      double member3{};

      INTROSPECTION_DATA(Thing, member1, member2, member3);
   };

   enum class myenum { first_value, second_value, third_value };
   INTROSPECTION_ENUM_DATA(myenum, first_value, second_value, third_value);

   TEST(macro, introspective) { ASSERT_TRUE(concepts::Introspective<Thing>); }

   TEST(macro, member_count) { ASSERT_EQ(member_count<Thing>, 3); };

   TEST(macro, member_names) {
      ASSERT_EQ((member_name<Thing, 0>), std::string_view("member1"));
      ASSERT_EQ((member_name<Thing, 1>), std::string_view("member2"));
      ASSERT_EQ((member_name<Thing, 2>), std::string_view("member3"));
   }

   TEST(macro, member_types) {
      ASSERT_TRUE((std::same_as<Member_type<Thing, 0>, std::array<int, 2>>));
      ASSERT_TRUE((std::same_as<Member_type<Thing, 1>, int>));
      ASSERT_TRUE((std::same_as<Member_type<Thing, 2>, double>));
   }

   TEST(macro, introspective_enum) {
      ASSERT_TRUE(concepts::Introspective_enum<myenum>);
   }

   enum class not_introspective { a, b };
   TEST(macro, not_introspective_enum) {
      ASSERT_FALSE(concepts::Introspective_enum<not_introspective>);
   }

   TEST(macro, enum_value_count) { ASSERT_EQ(enum_value_count<myenum>, 3); }
   TEST(macro, enum_values) {
      ASSERT_EQ(enum_values<myenum>[ 0 ], myenum::first_value);
      ASSERT_EQ(enum_values<myenum>[ 1 ], myenum::second_value);
      ASSERT_EQ(enum_values<myenum>[ 2 ], myenum::third_value);
   };

   TEST(macro, enum_value_name_by_index) {
      ASSERT_EQ(
        enum_value_names<myenum>[ 0 ],
        "introspection::testing::myenum::first_value");
      ASSERT_EQ(
        enum_value_names<myenum>[ 1 ],
        "introspection::testing::myenum::second_value");
      ASSERT_EQ(
        enum_value_names<myenum>[ 2 ],
        "introspection::testing::myenum::third_value");
   }

   TEST(macro, unqualified_enum_value_name_by_index) {
      ASSERT_EQ(unqualified_enum_value_names<myenum>[ 0 ], "first_value");
      ASSERT_EQ(unqualified_enum_value_names<myenum>[ 1 ], "second_value");
      ASSERT_EQ(unqualified_enum_value_names<myenum>[ 2 ], "third_value");
   }

   TEST(macro, type_qualified_enum_value_name_by_index) {
      ASSERT_EQ(
        type_qualified_enum_value_names<myenum>[ 0 ],
        "myenum::first_value");
      ASSERT_EQ(
        type_qualified_enum_value_names<myenum>[ 1 ],
        "myenum::second_value");
      ASSERT_EQ(
        type_qualified_enum_value_names<myenum>[ 2 ],
        "myenum::third_value");
   }

} // end of namespace introspection::testing
