#pragma once

//
// ... introspection header files
//
#include <introspection/details/concepts.hpp>
#include <introspection/details/import.hpp>

namespace introspection::details {

  template<concepts::Introspective T>
  constexpr auto member_count =
    tuple_size_v<decltype(T::Metadata::member_pointers)>;

} // end of namespace introspection::details
