#pragma once

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
      concept Introspective_enum = details::Enum<T> && requires {
         ssize(details::enum_metadata(std::type_identity<T>{}).enum_values());
      };

   } // end of namespace concepts

} // end of namespace introspection
