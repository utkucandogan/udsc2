#pragma once

#include "phoneme.hpp"

namespace udsc2::v1_0
{

class Prenasal
{
public:
    static Phoneme creator(const std::u32string_view s, size_t& i);
    static Phoneme procedural_creator(Phoneme::Properties example, Phoneme::Properties ignore, int maxLength);
    static bool register_extension();
};

}
