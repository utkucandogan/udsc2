#pragma once

#include "phoneme.hpp"

namespace udsc2
{

class Procedural
{
public:
    using Creator  = std::function<Phoneme(const Phoneme::Properties, const Phoneme::Properties, size_t)>;
    using Modifier = std::function<bool(Phoneme&, const Phoneme::Properties, const Phoneme::Properties, size_t)>;

    static std::vector<Creator> prefixHandlers;
    static std::vector<Modifier> suffixHandlers;

    static int maxDifference;

    static Phoneme generate(const Phoneme::Properties example, const Phoneme::Properties ignore, int maxLenght);
};

}
