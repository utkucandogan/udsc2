#include "phoneme.hpp"

#include <algorithm>

namespace udsc2
{

const Phoneme Phoneme::NONE = Phoneme { };

std::vector<Phoneme> Phoneme::phonemes;
std::vector<Phoneme::Creator> Phoneme::prefixHandlers;
std::vector<Phoneme::Modifier> Phoneme::suffixHandlers;
std::vector<Phoneme::Comparator> Phoneme::comparators;

Phoneme Phoneme::create(const std::u32string_view s, size_t& i)
{
    Phoneme ret; // Value that we should return

    // This loops for all custom prefix handlers. Handlers should return Phoneme::None
    // if they did not handle the phoneme.
    for (const auto& f : prefixHandlers) {
        ret = f(s, i);
        if (ret != Phoneme::NONE) {
            return ret;
        }
    }

    // Search for known phonemes.
    auto iter = std::find_if(phonemes.cbegin(), phonemes.cend(), [&s, i](const Phoneme& p) -> bool {
        return s.substr(i, p.string.size()) == p.string;
    });
    // If found, copy; else unknown.
    if (iter != phonemes.cend()) {
        ret = *iter;
        i += ret.string.size();
    } else {
        ret = Phoneme { s.substr(i++, 1), Phoneme::NONE.properties };
        ret.properties.type = api::TYP_PHONEME_UNKNOWN;
    }

    // This loops for all custom suffix handlers. Handlers should return false
    // if they did not handle any suffixes.
    size_t j = 0;
    while (j < suffixHandlers.size() && i < s.size()) {
        if (suffixHandlers[j](ret, s, i)) {
            j = 0; // Suffix is handled. Return to start.
        } else {
            ++j; // Suffix is not handled yet. Continue searching.
        }
    } // We are out of the loop once we cannot handle any suffixes.

    return ret;
}

}
