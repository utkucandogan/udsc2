#include <udsc2/phoneme/phoneme.h>
#include "phoneme.hpp"

#include <limits>

namespace udsc2::api
{

int phonemeDifference(const api::PhonemeProperties pLeft, const api::PhonemeProperties pRight,
                      const api::PhonemeProperties ignore)
{
    constexpr auto popcount = [](int v) -> int {
        // This algorithm is optimized for 32 bit.
        // I have no idea how this works. Credit goes to Sean Eron Anderson.
        // http://graphics.stanford.edu/~seander/bithacks.html
        v = v - ( ( v >> 1 ) & 0x55555555 );
        v = ( v & 0x33333333 ) + ( ( v >> 2 ) & 0x33333333 );
        return ( ( v + ( v >> 4 ) & 0xF0F0F0F ) * 0x1010101 ) >> 24;
    };

    // These are tecnical 'Phonemes' such as start, end or whitespace. Only comparison that
    // we need is whether their types are same.
    if (pLeft.Type < 8 || pRight.Type < 8) {
        return pLeft.Type == pRight.Type ? 0 : std::numeric_limits<int>::max();
    }

    // Custom comparison methods that is defined by extension writers.
    for (auto f : udsc2::Phoneme::Comparators) {
        int i = f(pLeft, pRight, ignore);
        if (i != -1) return i;
    }

    // If types are not same directly get out. Note that this is not before the custom
    // comparators because extensions may need cross-type differences (such as vowel-semivowel
    // comparison).
    if (pLeft.Type != pRight.Type) {
        return std::numeric_limits<int>::max();
    }

    int ret = 0;
    switch (pLeft.Type) {
    case api::TYP_VOWEL:
        if (ignore.Roundness == api::ROU_NONE && pLeft.Roundness != pRight.Roundness) {
            return std::numeric_limits<int>::max();
        }

        if (ignore.Height == api::HEI_NONE) {
            ret += std::abs(pLeft.Height - pRight.Height);
        }

        if (ignore.Backness == api::BAC_NONE) {
            ret += std::abs(pLeft.Backness - pRight.Backness);
        }
    case api::TYP_CONSONANT:
        if (ignore.Release == api::REL_NORMAL && pLeft.Release != pRight.Release) {
            if (pLeft.Release == api::REL_NORMAL) {
                ret += 1;
            } else {
                return std::numeric_limits<int>::max();
            }
        }

        if (ignore.Voicing == api::VOI_NONE && pLeft.Voicing != pRight.Voicing) {
            ++ret;
        }

        ret += popcount(( pLeft.PoA ^ pRight.PoA ) & ~ignore.PoA);
        ret += popcount(( pLeft.MoA ^ pRight.MoA ) & ~ignore.MoA);

        return ret;
    }

    return std::numeric_limits<int>::max();
}

}
