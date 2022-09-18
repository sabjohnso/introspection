#pragma once

//
// ... introspection header files
//
#include <introspection/details/import.hpp>
#include <introspection/details/typedata.hpp>

namespace introspection::details {

   template<auto Target_value>
   constexpr string_view
   pretty_function_value() {
      return string_view(__PRETTY_FUNCTION__);
   }

   constexpr auto
   start_of_value_name(string_view raw) {
      constexpr string_view pattern = "Target_value = ";
      return raw.find(pattern) + size(pattern);
   }

   constexpr auto
   size_of_value_name(string_view raw_stripped_of_front) {
      const auto colon = raw_stripped_of_front.find_first_of(";");
      const auto bracket = raw_stripped_of_front.find_first_of("]");
      return min(colon, bracket);
   }

   template<auto value>
   constexpr string_view
   lookup_value_name() {
      const string_view raw = pretty_function_value<value>();
      const auto offset = start_of_value_name(raw);
      const auto count =
        size_of_value_name(raw.substr(offset, size(raw) - offset));
      return raw.substr(offset, count);
   }

   constexpr string_view
   enum_type_and_name(
     string_view full_type_name,
     string_view unqualified_type_name,
     string_view value_name) {
      const auto offset =
        value_name.rfind(unqualified_type_name, size(full_type_name));
      return value_name.substr(offset, size(value_name) - offset);
   }

   template<typename T>
   concept Enum = is_enum_v<T>;

   template<Enum auto value>
   constexpr string_view enum_value_name = lookup_value_name<value>();

   template<Enum auto value>
   constexpr string_view
     unqualified_enum_value_name = remove_qualification(enum_value_name<value>);

   template<Enum auto value>
   constexpr string_view type_qualified_enum_value_name = enum_type_and_name(
     type_name<decltype(value)>,
     unqualified_type_name<decltype(value)>,
     enum_value_name<value>);

   template<typename T>
   void
   enum_metadata_function(type_identity<T>) {}

   struct enum_metadata_fn {
      template<Enum T>
      constexpr auto
      operator()(type_identity<T>) const {
         return enum_metadata_function(type_identity<T>{});
      }
   };

   template<typename T>
   constexpr T static_const{};

   constexpr const auto& enum_metadata = static_const<enum_metadata_fn>;

   template<Enum T>
   constexpr auto
     enum_value_count = size(enum_metadata(type_identity<T>{}).enum_values());

   template<Enum T>
   constexpr auto enum_values = enum_metadata(type_identity<T>{}).enum_values();

   template<Enum T>
   constexpr auto enum_value_names = []<auto... I>(index_sequence<I...>) {
      return array{enum_value_name<enum_values<T>[ I ]>...};
   }
   (make_index_sequence<enum_value_count<T>>());

   template<Enum T>
   constexpr auto
     type_qualified_enum_value_names = []<auto... I>(index_sequence<I...>) {
      return array{type_qualified_enum_value_name<enum_values<T>[ I ]>...};
   }
   (make_index_sequence<enum_value_count<T>>());

   template<Enum T>
   constexpr auto
     unqualified_enum_value_names = []<auto... I>(index_sequence<I...>) {
      return array{unqualified_enum_value_name<enum_values<T>[ I ]>...};
   }
   (make_index_sequence<enum_value_count<T>>());

} // end of namespace introspection::details
