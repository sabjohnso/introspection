#pragma once

//
// ... introspection header files
//
#include <introspection/details/concepts.hpp>
#include <introspection/details/metadata_query.hpp>
#include <introspection/details/typedata.hpp>

namespace introspection {

   namespace concepts {

      using ::introspection::details::concepts::Introspective;

   } // end of namespace concepts

   using ::introspection::details::member_count;
   using ::introspection::details::member_name;
   using ::introspection::details::Member_type;

   using ::introspection::details::bare_type_name;
   using ::introspection::details::type_name;
   using ::introspection::details::unqualified_type_name;
   using ::introspection::details::unspecialized_type_name;

} // end of namespace introspection
