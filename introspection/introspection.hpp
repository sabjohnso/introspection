#pragma once

//
// ... Standard header files
//
#include <iostream>
#include <string>
#include <string_view>

//
// ... introspection header files
//
#include <introspection/details/concepts.hpp>
#include <introspection/details/enumdata.hpp>
#include <introspection/details/metadata_query.hpp>
#include <introspection/details/typedata.hpp>

namespace introspection {

   using ::introspection::details::bare_type_name;
   using ::introspection::details::enum_value_count;
   using ::introspection::details::enum_value_name;
   using ::introspection::details::enum_value_names;
   using ::introspection::details::enum_values;
   using ::introspection::details::member_count;
   using ::introspection::details::member_name;
   using ::introspection::details::member_pointer;
   using ::introspection::details::Member_type;
   using ::introspection::details::type_name;
   using ::introspection::details::type_qualified_enum_value_name;
   using ::introspection::details::type_qualified_enum_value_names;
   using ::introspection::details::unqualified_enum_value_name;
   using ::introspection::details::unqualified_enum_value_names;
   using ::introspection::details::unqualified_type_name;
   using ::introspection::details::unspecialized_type_name;

   namespace concepts {

      using ::introspection::details::concepts::Introspective;
      template<typename T>
      concept Introspective_enum =
        details::Enum<T> &&
        requires {
           ssize(details::enum_metadata(std::type_identity<T>{}).enum_values());
        };

   } // end of namespace concepts

   namespace terse {

      template<concepts::Introspective_enum T>
      constexpr std::string_view
      to_string_view(const T& value) {
         constexpr auto recur = []<std::size_t Index, std::size_t... Indices>(
           auto recur,
           const auto& value,
           std::index_sequence<Index, Indices...>) {
            if constexpr(sizeof...(Indices) == 0) {
               return unqualified_enum_value_names<T>[ Index ];
            } else {
               return value == enum_values<T>[ Index ]
                      ? unqualified_enum_value_names<T>[ Index ]
                      : recur(recur, value, std::index_sequence<Indices...>{});
            }
         };
         return recur(
           recur,
           value,
           std::make_index_sequence<enum_value_count<T>>());
      }

      std::string
      to_string(const auto& value) {
         return {value};
      }

      template<concepts::Introspective_enum T>
      std::ostream&
      operator<<(std::ostream& os, const T& value) {
         return os << to_string_view(value);
      }

   } // end of namespace terse

   namespace verbose {

      template<concepts::Introspective_enum T>
      constexpr std::string_view
      to_string_view(const T& value) {
         constexpr auto recur = []<std::size_t Index, std::size_t... Indices>(
           auto recur,
           const auto& value,
           std::index_sequence<Index, Indices...>) {
            if constexpr(sizeof...(Indices) == 0) {
               return enum_value_names<T>[ Index ];
            } else {
               return value == enum_values<T>[ Index ]
                      ? enum_value_names<T>[ Index ]
                      : recur(recur, value, std::index_sequence<Indices...>{});
            }
         };
         return recur(
           recur,
           value,
           std::make_index_sequence<enum_value_count<T>>());
      }

      std::string
      to_string(const auto& value) {
         return {value};
      }

      template<concepts::Introspective_enum T>
      std::ostream&
      operator<<(std::ostream& os, const T& value) {
         return os << to_string_view(value);
      }

   } // end of namespace verbose

   namespace type_qualified {

      template<concepts::Introspective_enum T>
      constexpr std::string_view
      to_string_view(const T& value) {
         constexpr auto recur = []<std::size_t Index, std::size_t... Indices>(
           auto recur,
           const auto& value,
           std::index_sequence<Index, Indices...>) {
            if constexpr(sizeof...(Indices) == 0) {
               return type_qualified_enum_value_names<T>[ Index ];
            } else {
               return value == enum_values<T>[ Index ]
                      ? type_qualified_enum_value_names<T>[ Index ]
                      : recur(recur, value, std::index_sequence<Indices...>{});
            }
         };
         return recur(
           recur,
           value,
           std::make_index_sequence<enum_value_count<T>>());
      }

      std::string
      to_string(const auto& value) {
         return {value};
      }

      template<concepts::Introspective_enum T>
      std::ostream&
      operator<<(std::ostream& os, const T& value) {
         return os << to_string_view(value);
      }

   } // namespace type_qualified
} // end of namespace introspection
