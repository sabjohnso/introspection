#pragma once
//
// ... standard header files
//
#include <boost/preprocessor.hpp>
#include <string_view>

#define __S_QUOTE_AUX(...) #__VA_ARGS__
#define __S_QUOTE(a, b, ...)                                                   \
   std::string_view { __S_QUOTE_AUX(__VA_ARGS__) }

#define __S_POP_AUX(...) __VA_ARGS__
#define __S_POP(...) __S_POP_AUX __VA_ARGS__

#define __S_SEQ_TO_VARIADIC(seq) __S_POP(BOOST_PP_SEQ_TO_TUPLE(seq))

#define __S_TRANSFORM(OP, data, ...)                                           \
   __S_SEQ_TO_VARIADIC(                                                        \
     BOOST_PP_SEQ_TRANSFORM(OP, data, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))

#define __S_MEMBER_POINTER(_ignored, struct_name, member_name)                 \
   &struct_name::member_name

#define __S_MEMBER_POINTERS(struct_name, ...)                                  \
   __S_TRANSFORM(__S_MEMBER_POINTER, struct_name, __VA_ARGS__)

#define __S_MEMBER_NAMES(...) __S_TRANSFORM(__S_QUOTE, , __VA_ARGS__)

#define INTROSPECTION_DATA(name, ...)                                          \
   struct Metadata {                                                           \
      static constexpr ::std::tuple member_pointers{                           \
        __S_MEMBER_POINTERS(name, __VA_ARGS__)};                               \
      static constexpr ::std::tuple member_names{                              \
        __S_MEMBER_NAMES(__VA_ARGS__)};                                        \
   }

#define INTROSPECTION_ENUM_DATA(name, ...)                                     \
   constexpr auto enum_metadata_function(::std::type_identity<name>) {         \
      struct Enum_metadata {                                                   \
         using enum name;                                                      \
         constexpr auto                                                        \
         enum_values() const {                                                 \
            return ::std::array{__VA_ARGS__};                                  \
         }                                                                     \
      };                                                                       \
      return Enum_metadata{};                                                  \
   }
