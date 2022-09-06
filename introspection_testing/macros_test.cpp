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

} // end of namespace introspection::testing
