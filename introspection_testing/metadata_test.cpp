//
// ... Standard header files
//
#include <array>
#include <bits/utility.h>
#include <iostream>
#include <string_view>
#include <tuple>

//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... introspection header files
//
#include <introspection/introspection.hpp>

namespace introspection::testing {

  struct Example_with_metadata
  {

    int a{};
    int b{};
    double c{};

    static_assert(
      std::is_member_pointer_v<decltype(&Example_with_metadata::a)>);

    struct Metadata
    {
      static constexpr std::tuple member_pointers{
        &Example_with_metadata::a,
        &Example_with_metadata::b,
        &Example_with_metadata::c};

      static constexpr std::tuple member_names{
        std::string_view("a"),
        std::string_view("b"),
        std::string_view("c")};
    };
  };

  TEST(metadata, introspection)
  {
    ASSERT_TRUE(concepts::Introspective<Example_with_metadata>);
  }

  struct Example_without_metadata
  {
    int a{};
    int b{};
    double c{};
  };

  TEST(metadata, introspective_fail_without_metadata)
  {
    ASSERT_FALSE(concepts::Introspective<Example_without_metadata>);
  }

  struct Example_without_member_pointers
  {
    int a{};
    int b{};
    double c{};

    struct Metadata
    {
      static constexpr std::tuple member_names{
        std::string_view("a"),
        std::string_view("b"),
        std::string_view("c")};
    };
  };

  TEST(metadata, introspective_fail_without_member_pointers)
  {
    ASSERT_FALSE(concepts::Introspective<Example_without_member_pointers>);
  }

  struct Example_without_member_pointers_tuple
  {
    int a{};
    int b{};
    double c{};

    struct Metadata
    {
      static constexpr auto member_pointers = 3;
      static constexpr std::tuple member_names{
        std::string_view("a"),
        std::string_view("b"),
        std::string_view("c")};
    };
  };

  TEST(metadata, introspective_fail_without_member_pointers_tuple)
  {
    ASSERT_FALSE(
      concepts::Introspective<Example_without_member_pointers_tuple>);
  }

  struct Example_without_member_pointers_are_member_pointers
  {
    int a{};
    int b{};
    double c{};

    struct Metadata
    {
      static constexpr std::tuple member_pointers{1, 2, 3};
      static constexpr std::tuple member_names{
        std::string_view("a"),
        std::string_view("b"),
        std::string_view("c")};
    };
  };

  TEST(metadata, introspective_fail_without_member_pointers_are_member_pointers)
  {
    ASSERT_FALSE(concepts::Introspective<
                 Example_without_member_pointers_are_member_pointers>);
  }

  struct Example_without_member_names
  {
    int a{};
    int b{};
    double c{};

    struct Metadata
    {
      static constexpr std::tuple member_pointers{
        &Example_with_metadata::a,
        &Example_with_metadata::b,
        &Example_with_metadata::c};
    };
  };

  TEST(metadata, introspective_fail_without_member_names)
  {
    ASSERT_FALSE(concepts::Introspective<Example_without_member_names>);
  }

  struct Example_without_memeber_names_tuple
  {
    int a{};
    int b{};
    double c{};
    struct Metadata
    {
      static constexpr std::tuple member_pointers{
        &Example_with_metadata::a,
        &Example_with_metadata::b,
        &Example_with_metadata::c};

      static constexpr std::array member_names{
        std::string_view("a"),
        std::string_view("b"),
        std::string_view("c")};
    };
  };

  TEST(metadata, introspective_fail_without_member_names_tuple)
  {
    EXPECT_FALSE(concepts::Introspective<Example_without_memeber_names_tuple>);
  }

  struct Example_without_memeber_names_are_string_like
  {
    int a{};
    int b{};
    double c{};
    struct Metadata
    {
      static constexpr std::tuple member_pointers{
        &Example_with_metadata::a,
        &Example_with_metadata::b,
        &Example_with_metadata::c};
      static constexpr std::tuple member_names{1, 2, 3};
    };
  };

  TEST(metadata, introspective_fail_without_member_names_are_string_like)
  {
    EXPECT_FALSE(
      concepts::Introspective<Example_without_memeber_names_are_string_like>);
  }

  struct Example_without_pointers_and_names_same_length
  {

    int a{};
    int b{};
    double c{};

    static_assert(
      std::is_member_pointer_v<decltype(&Example_with_metadata::a)>);

    struct Metadata
    {
      static constexpr std::tuple member_pointers{
        &Example_with_metadata::a,
        &Example_with_metadata::b,
        &Example_with_metadata::c};

      static_assert([]<auto... Index>(std::index_sequence<Index...>) {
        return (
          std::is_member_pointer_v<
            std::remove_cvref_t<decltype(std::get<Index>(member_pointers))>> &&
          ...);
      }(std::make_index_sequence<3>()));

      static constexpr std::tuple member_names{
        std::string_view("a"),
        std::string_view("b")};
    };
  };

  TEST(metadata, introspective_fail_without_pointers_and_names_same_length)
  {
    EXPECT_FALSE(
      concepts::Introspective<Example_without_pointers_and_names_same_length>);
  }

  TEST(metadata, member_count)
  {
    EXPECT_EQ(member_count<Example_with_metadata>, 3);
  }

} // end of namespace introspection::testing
