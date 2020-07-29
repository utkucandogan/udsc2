#pragma once

#include "phoneme.hpp"

namespace udsc2::v1_0
{

class Tie
{
public:
    static bool modifier(Phoneme& p, const std::u32string_view s, size_t& i);
    static Phoneme procedural_creator(Phoneme::Properties example, Phoneme::Properties ignore, int maxLength);
    static bool procedural_modifier(Phoneme& p, Phoneme::Properties example, Phoneme::Properties ignore, size_t maxLength);
    static bool register_extension() noexcept;

private:
    static void combine(Phoneme& left, const Phoneme& right);
};

}
