#include <udsc2/phoneme/phoneme.h>
#include "phoneme.hpp"
#include "util/bit.h"

#include <limits>

namespace udsc2::api
{

int phoneme_difference(const api::PhonemeProperties pLeft, const api::PhonemeProperties pRight,
                       const api::PhonemeProperties ignore)
{
    // These are tecnical 'Phonemes' such as start, end or whitespace. Only comparison that
    // we need is whether their types are same.
    if (pLeft.type < 8 || pRight.type < 8) {
        return pLeft.type == pRight.type ? 0 : std::numeric_limits<int>::max();
    }

    // Custom comparison methods that is defined by extension writers.
    for (auto f : udsc2::Phoneme::comparators) {
        int i = f(pLeft, pRight, ignore);
        if (i != -1) return i;
    }

    // If types are not same directly get out. Note that this is not before the custom
    // comparators because extensions may need cross-type differences (such as vowel-semivowel
    // comparison).
    if (pLeft.type != pRight.type) {
        return std::numeric_limits<int>::max();
    }

    int ret = 0;
    switch (pLeft.type) {
    case api::TYP_VOWEL:
        if (ignore.roundness == api::ROU_NONE && pLeft.roundness != pRight.roundness) {
            return std::numeric_limits<int>::max();
        }

        if (ignore.height == api::HEI_NONE) {
            ret += std::abs(pLeft.height - pRight.height);
        }

        if (ignore.backness == api::BAC_NONE) {
            ret += std::abs(pLeft.backness - pRight.backness);
        }
    case api::TYP_CONSONANT:
        if (ignore.release == api::REL_NORMAL && pLeft.release != pRight.release) {
            if (pLeft.release == api::REL_NORMAL) {
                ret += 1;
            } else {
                return std::numeric_limits<int>::max();
            }
        }

        if (ignore.voicing == api::VOI_NONE && pLeft.voicing != pRight.voicing) {
            ++ret;
        }

        ret += util::popcount(( pLeft.poa ^ pRight.poa ) & ~ignore.poa);
        ret += util::popcount(( pLeft.moa ^ pRight.moa ) & ~ignore.moa);

        return ret;
    }

    return std::numeric_limits<int>::max();
}

}
