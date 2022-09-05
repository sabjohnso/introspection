#pragma once

//
// ... introspection header files
//
#include <introspection/details/import.hpp>

namespace introspection::details::concepts {

   template<typename T>
   concept Bare = same_as<T, remove_cvref_t<T>>;

   template<typename T>
   concept Bare_character = Bare<T> &&
     (same_as<T, char> || same_as<T, signed char> ||
      same_as<T, unsigned char> || same_as<T, wchar_t> ||
      same_as<T, char8_t> || same_as<T, char16_t> ||
      same_as<T, char32_t>);

   template<typename T>
   concept Character = Bare_character<remove_cvref_t<T>>;

   template<typename T>
   concept String_like = requires(T x) {
      std::size(x);
      { x[ 0 ] } -> Character;
   };

   template<typename T>
   concept Tuple = requires(T x) {
      []<typename... Ts>(tuple<Ts...>) {}(x);
   };

   template<typename T>
   concept Has_metadata = requires {
      typename T::Metadata;
   };

   template<typename T>
   concept Has_member_pointers = Has_metadata<T> && requires {
      T::Metadata::member_pointers;
   };

   template<typename T>
   concept Has_conforming_member_pointers = Has_member_pointers<T> &&
     Tuple<decltype(T::Metadata::member_pointers)> &&[]<auto... Index>(
       index_sequence<Index...>) {
      return (
        is_member_pointer_v<remove_cvref_t<decltype(get<Index>(
          T::Metadata::member_pointers))>> &&
        ...);
   }
   (make_index_sequence<
     tuple_size_v<decltype(T::Metadata::member_pointers)>>());

   template<typename T>
   concept Has_member_names = Has_metadata<T> && requires {
      T::Metadata::member_names;
   };

   template<typename T>
   concept Has_conforming_member_names = Has_member_pointers<T> &&
     Tuple<decltype(T::Metadata::member_names)> &&[]<auto... Index>(
       index_sequence<Index...>) {
      return (
        String_like<remove_cvref_t<decltype(get<Index>(
          T::Metadata::member_names))>> &&
        ...);
   }
   (make_index_sequence<
     tuple_size_v<decltype(T::Metadata::member_names)>>());

   template<typename T>
   concept Introspective = Has_conforming_member_pointers<T> &&
     Has_conforming_member_names<T> &&
     (tuple_size_v<decltype(T::Metadata::member_pointers)> ==
      tuple_size_v<decltype(T::Metadata::member_names)>);

} // end of namespace introspection::details::concepts
