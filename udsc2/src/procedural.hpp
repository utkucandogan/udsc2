#pragma once

#include "phoneme.hpp"

namespace udsc2
{

class Procedural
{
public:
    using Creator  = std::function<Phoneme(const api::PhonemeProperties, const api::PhonemeProperties, size_t)>;
    using Modifier = std::function<bool(Phoneme&, const api::PhonemeProperties, const api::PhonemeProperties, size_t)>;

    static std::vector<Creator> PrefixHandlers;
    static std::vector<Modifier> SuffixHandlers;

    static int MaxDifference;

    static Phoneme generate(const api::PhonemeProperties example, const api::PhonemeProperties ignore, int maxLenght);
};

}
