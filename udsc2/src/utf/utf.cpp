#include "utf.hpp"

namespace udsc2::utf
{

template<size_t I>
inline char get_six_bit(const char32_t c)
{
    constexpr char32_t six_bit = 0b0000'0000'0000'0000'0000'0000'0011'1111;
    constexpr char32_t six_bit_shifted = six_bit << ( I * 6 );
    return static_cast<char> ( ( c & six_bit_shifted ) >> ( I * 6 ) );
}

template<>
std::basic_string<char> convert_to(std::basic_string_view<char32_t> s)
{
    std::string ret;
    ret.reserve(s.size() * 2); // At max word count of UTF-8 is four times
    // of the UTF-32. However, most users will probably use lower codepoints
    // so that word count is less than two times. So two times is an enough
    // approximation for the purposes of this function.

    for (const auto c : s) {
        if (c < 0x80) {
            ret.push_back(static_cast<char> ( c ));
        } else if (c < 0x800) {
            ret.push_back(0b1100'0000 | get_six_bit<1>(c));
            ret.push_back(0b1000'0000 | get_six_bit<0>(c));
        } else if (c < 0x1'0000) {
            ret.push_back(0b1110'0000 | get_six_bit<2>(c));
            ret.push_back(0b1000'0000 | get_six_bit<1>(c));
            ret.push_back(0b1000'0000 | get_six_bit<0>(c));
        } else if (c < 0x11'0000) {
            ret.push_back(0b1111'0000 | get_six_bit<3>(c));
            ret.push_back(0b1000'0000 | get_six_bit<2>(c));
            ret.push_back(0b1000'0000 | get_six_bit<1>(c));
            ret.push_back(0b1000'0000 | get_six_bit<0>(c));
        } else {
            // replacement character U+FFFD
            ret.push_back('\xEF');
            ret.push_back('\xBF');
            ret.push_back('\xBD');
        }
    }
    ret.shrink_to_fit();
    return std::move(ret);
}

template<>
std::basic_string<char32_t> convert_to(std::basic_string_view<char> s)
{
    std::u32string ret;
    ret.reserve(s.size() / 2); // At max word count of UTF-8 is four times
    // of the UTF-32. However, most users will probably use lower codepoints
    // so that word count is less than two times. So two times is an enough
    // approximation for the purposes of this function.

    for (size_t i = 0, len = s.size() ; i < len ; ++i) {
        unsigned char u = static_cast<unsigned char> ( s[i] );

        auto trailing_bytes = [&](char32_t c, const size_t count) {
            for (size_t j = 0 ; j < count ; ++j) {
                u = static_cast <unsigned char> ( s[i + 1 + j] );
                if (u < 0b1100'0000 && u > 0b1000'0000) {
                    c <<= 6;
                    c |= u & 0b0011'1111;
                } else {
                    ret.push_back(U'\uFFFD');
                    return;
                }
            }
            i += count;
            ret.push_back(c);
        };

        if (u < 0x80) {
            ret.push_back(u);
        } else if (u < 0b1110'0000) {
            trailing_bytes(u & 0b0001'1111, 1);
        } else if (u < 0b1111'0000) {
            trailing_bytes(u & 0b0000'1111, 2);
        } else if (u < 0b1111'1000) {
            trailing_bytes(u & 0b0000'0111, 3);
        } else {
            ret.push_back(U'\uFFFD');
        }
    }
    ret.shrink_to_fit();
    return std::move(ret);
}

}