#pragma once

#include <string_view>
#include <string>

namespace udsc2::utf
{

template<typename TO, typename FROM>
std::basic_string<TO> convert_to(std::basic_string_view<FROM> s)
{
    static_assert ( false, "Function is not implemented for given types!" );
}

template<typename TO, typename FROM>
std::basic_string<TO> convert_to(std::basic_string<FROM>& s)
{
    return convert_to<TO, FROM>(std::basic_string_view<FROM>(s));
}

template<typename TO, typename FROM>
std::basic_string<TO> convert_to(std::basic_string<FROM>&& s)
{
    return convert_to<TO, FROM>(std::basic_string_view<FROM>(std::move(s)));
}

template<typename TO, typename FROM>
std::basic_string<TO> convert_to(const FROM* s)
{
    return convert_to<TO, FROM>(std::basic_string_view<FROM>(s));
}

template<>
std::basic_string<char> convert_to<>(std::basic_string_view<char32_t> s);

template<>
std::basic_string<char32_t> convert_to<>(std::basic_string_view<char> s);

}
