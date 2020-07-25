#pragma once

#include <string>
#include <memory>
#include <vector>
#include <functional>

#include <udsc2/phoneme/phoneme.h>

namespace udsc2
{

class Phoneme
{
public:
    using Properties = api::PhonemeProperties;

    std::u32string string;
    Properties properties;

    Phoneme(std::u32string_view string, Properties properties)
        : string(string), properties(properties)
    { }

    Phoneme() : Phoneme(U"", api::PHO_NONE) { }

    Phoneme(uint8_t type) : Phoneme()
    {
        properties.type = type;
    }

    int difference(const Properties p, const Properties ignore) const noexcept
    {
        return phoneme_difference(properties, p, ignore);
    }

    bool operator==(const Phoneme& p) const noexcept
    {
        return phoneme_difference(properties, p.properties, NONE.properties) == 0;
    }

    bool operator!=(const Phoneme& p) const noexcept
    {
        return phoneme_difference(properties, p.properties, NONE.properties) != 0;
    }

#pragma region Static Members
public:
    using Creator    = std::function<Phoneme(const std::u32string_view, size_t&)>;
    using Modifier   = std::function<bool(Phoneme&, const std::u32string_view, size_t&)>;
    using Comparator = std::function<int(const Properties, const Properties, const Properties)>;

    static std::vector<Phoneme> phonemes;
    static std::vector<Creator> prefixHandlers;
    static std::vector<Modifier> suffixHandlers;
    static std::vector<Comparator> comparators;

    static const Phoneme NONE;

    static Phoneme create(const std::u32string_view s, size_t& i);
};
#pragma endregion

}
