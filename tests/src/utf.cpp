#include <catch2/catch.hpp>

#ifndef UDSC2_SHARED

#include "utf/utf.hpp"

namespace udsc2::tests
{

TEST_CASE("Testing from UTF-8 to UTF-32.", "[UTF]")
{
    auto u8 = std::string { u8"ɾ̞eaˡख़㓗" };
    auto u32 = std::u32string { U"ɾ̞eaˡख़㓗" };

    auto ret = utf::convert_to<char32_t>(u8);

    REQUIRE(u32 == ret);
}

TEST_CASE("Testing from UTF-32 to UTF-8.", "[UTF]")
{
    auto u8 = std::string { u8"ɾ̞eaˡख़㓗" };
    auto u32 = std::u32string { U"ɾ̞eaˡख़㓗" };

    auto ret = utf::convert_to<char>(u32);

    REQUIRE(u8 == ret);
}

}
#endif
