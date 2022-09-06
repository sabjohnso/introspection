#pragma once

//
// ... introspection header files
//
#include <introspection/details/import.hpp>

namespace introspection::details {

   template<typename Target_type>
   constexpr string_view
   pretty_function(type_identity<Target_type>) {
      return string_view(__PRETTY_FUNCTION__);
   }

   constexpr auto
   start_of_type_name(string_view raw) {
      constexpr string_view pattern = "Target_type = ";
      return raw.find(pattern) + size(pattern);
   }

   constexpr auto
   size_of_type_name(string_view raw_stripped_of_front) {
      const auto colon = raw_stripped_of_front.find_first_of(";");
      const auto bracket = raw_stripped_of_front.find_first_of("]");
      return min(colon, bracket);
   }

   constexpr string_view
   lookup_type_name(auto type) {
      const string_view raw = pretty_function(type);
      const auto offset = start_of_type_name(raw);
      const auto count =
        size_of_type_name(raw.substr(offset, size(raw) - offset));
      return raw.substr(offset, count);
   }

   constexpr bool
   isspecialized(string_view name) {
      return name[ size(name) - 1 ] == '>';
   }

   constexpr string_view
   remove_specialization(string_view name) {
      constexpr auto recur =
        [](auto recur, string_view name, int depth) -> string_view {
         constexpr auto dig =
           [](auto recur, string_view name, int depth) -> string_view {
            const auto next_close = name.find_last_of(">");
            const auto next_open = name.find_last_of("<");
            // return recur(recur, name.substr(0, next_open), 0);
            return (next_close == string_view::npos || (next_close < next_open))
                   ? recur(recur, name.substr(0, next_open), depth - 1)
                   : recur(recur, name.substr(0, next_close), depth + 1);
         };
         return depth > 0 ? dig(recur, name, depth) : name;
      };

      return isspecialized(name)
             ? recur(recur, name.substr(0, size(name) - 1), 1)
             : name;
   }

   constexpr string_view
   remove_qualification(string_view name) {
      const string_view unspecialized_name = remove_specialization(name);
      const auto last_delimiter = unspecialized_name.find_last_of("::");
      return last_delimiter == string_view::npos
             ? name
             : name.substr(last_delimiter + 1, size(name) - last_delimiter);
   }

   template<typename T>
   constexpr string_view
     type_name = lookup_type_name(type_identity<remove_cvref_t<T>>{});

   template<typename T>
   constexpr string_view
     unqualified_type_name = remove_qualification(type_name<T>);

   template<typename T>
   constexpr string_view
     unspecialized_type_name = remove_specialization(type_name<T>);

   template<typename T>
   constexpr string_view
     bare_type_name = remove_specialization(remove_qualification(type_name<T>));

} // namespace introspection::details
