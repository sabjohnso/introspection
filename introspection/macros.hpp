#pragma once

#define INSPECTABLE(...)                                               \
   struct Metadata {                                                   \
      static constexpr ::std::tuple member_pointers{};                 \
      static constexpr ::std::tuple member_names{};                    \
   }
