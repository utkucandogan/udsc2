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
    using List       = std::vector<Phoneme>;

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

    Phoneme(std::u32string_view string, uint8_t voicing, uint16_t poa, uint16_t moa)
        : Phoneme(string, Properties {
            api::TYP_CONSONANT,
            0u,
            voicing,
            api::REL_NORMAL,
            api::HEI_NONE,
            api::BAC_NONE,
            api::ROU_NONE,
            0u,
            poa,
            moa,
            0u,
            0u,
            0u,
            nullptr,
            nullptr
        })
    { }

    Phoneme(std::u32string_view string, uint8_t voicing, uint8_t height, uint8_t backness, uint8_t roundness)
        : Phoneme(string, Properties {
            api::TYP_VOWEL,
            0u,
            voicing,
            api::REL_NORMAL,
            height,
            backness,
            roundness,
            0u,
            api::POA_NONE,
            api::MOA_NONE,
            0u,
            0u,
            0u,
            nullptr,
            nullptr
        })
    { }

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
    using Comparator = std::function<int(Properties, Properties, Properties)>;

    static std::vector<Phoneme> phonemes;
    static std::vector<Creator> prefixHandlers;
    static std::vector<Modifier> suffixHandlers;
    static std::vector<Comparator> comparators;

    static const Phoneme NONE;

    static Phoneme create(const std::u32string_view s, size_t& i);
};
#pragma endregion

}
