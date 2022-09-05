//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... introspection header files
//
#include <introspection/introspection.hpp>
#include <introspection/macros.hpp>

namespace introspection::testing {

   struct Thing {
      INSPECTABLE(

        ((std::array<int, 2>), member1, {}),

        (int, member2, {}),

        (double, member3, [ 2 ] {}));
   };

   TEST(macro, introspective) {
      ASSERT_TRUE(concepts::Introspective<Thing>);
   }

   TEST(macro, member_count) { ASSERT_EQ(member_count<Thing>, 3); }

} // end of namespace introspection::testing
