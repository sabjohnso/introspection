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

   template<concepts::Introspective T, auto Index>
   requires(Index >= 0 && Index < member_count<T>) using Member_type =
     remove_cvref_t<decltype([](auto x, auto ptr) {
        return x.*ptr;
     }(declval<T>(), get<Index>(T::Metadata::member_pointers)))>;

   template<concepts::Introspective T, auto Index>
   requires(
     Index >= 0 && Index < member_count<T>) constexpr auto member_name =
     get<Index>(T::Metadata::member_names);

} // end of namespace introspection::details
