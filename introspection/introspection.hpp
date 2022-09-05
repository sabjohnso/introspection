#pragma once

//
// ... introspection header files
//
#include <introspection/details/concepts.hpp>
#include <introspection/details/metadata_query.hpp>

namespace introspection {

  namespace concepts {

    using ::introspection::details::concepts::Introspective;

  } // end of namespace concepts

  using ::introspection::details::member_count;

} // end of namespace introspection
