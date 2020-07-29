#pragma once

#include "phoneme.hpp"

namespace udsc2
{

class Procedural
{
public:
    using Creator  = std::function<Phoneme(Phoneme::Properties, Phoneme::Properties, size_t)>;
    using Modifier = std::function<bool(Phoneme&, Phoneme::Properties, Phoneme::Properties, size_t)>;

    static std::vector<Creator> prefixHandlers;
    static std::vector<Modifier> suffixHandlers;

    static int maxDifference;

    static Phoneme generate(Phoneme::Properties example, Phoneme::Properties ignore, int maxLenght);
};

}
