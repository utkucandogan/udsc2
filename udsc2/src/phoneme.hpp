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
    std::u32string String;
    api::PhonemeProperties Properties;

    Phoneme(std::u32string_view string, api::PhonemeProperties properties)
        : String(string), Properties(properties)
    { }

    Phoneme(uint8_t type) : String(U""), Properties {
        type,
        0u,
        api::VOI_NONE,
        api::REL_NORMAL,
        api::HEI_NONE,
        api::BAC_NONE,
        api::ROU_NONE,
        0u,
        api::POA_NONE,
        api::MOA_NONE,
        0u,
        0u,
        0u,
        nullptr,
        nullptr
    } { }

    Phoneme() : Phoneme(api::TYP_NONE) { }

    int difference(const api::PhonemeProperties p, const api::PhonemeProperties ignore) const noexcept
    {
        return phonemeDifference(Properties, p, ignore);
    }

    bool operator==(const Phoneme& p) const noexcept
    {
        return phonemeDifference(Properties, p.Properties, None.Properties) == 0;
    }

    bool operator!=(const Phoneme& p) const noexcept
    {
        return phonemeDifference(Properties, p.Properties, None.Properties) != 0;
    }

#pragma region Static Members
public:
    using Creator    = std::function<Phoneme(const std::u32string_view, size_t&)>;
    using Modifier   = std::function<bool(Phoneme&, const std::u32string_view, size_t&)>;
    using Comparator = std::function<int(const api::PhonemeProperties, const api::PhonemeProperties,
                                         const api::PhonemeProperties)>;

    static std::vector<Phoneme> Phonemes;
    static std::vector<Creator> PrefixHandlers;
    static std::vector<Modifier> SuffixHandlers;
    static std::vector<Comparator> Comparators;

    static const Phoneme None;

    static Phoneme create(const std::u32string_view s, size_t& i);
};
#pragma endregion

}
