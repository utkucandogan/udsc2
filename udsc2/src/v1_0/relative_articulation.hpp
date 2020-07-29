#pragma once

#include "phoneme.hpp"

#include <array>

namespace udsc2::v1_0
{

class RelativeArticulation
{
public:
    static bool modifier(Phoneme& p, const std::u32string_view s, size_t& i);
    static bool procedural_modifier(Phoneme& p, Phoneme::Properties example, Phoneme::Properties ignore, size_t maxLength);
    static bool register_extension() noexcept;

private:
    static const std::array<char32_t, 10> deepGlyphs;
    static const std::array<std::pair<char32_t, char32_t>, 4> modifierPairs;


    static bool raise(Phoneme::Properties& p);
    static bool lower(Phoneme::Properties& p);

    static bool advance(Phoneme::Properties& p);
    static bool retract(Phoneme::Properties& p);

    static bool centeralize(Phoneme::Properties& p);
    static bool midcenteralize(Phoneme::Properties& p);
};

}
