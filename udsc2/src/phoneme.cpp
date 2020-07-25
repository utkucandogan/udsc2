#include "phoneme.hpp"

#include <algorithm>

namespace udsc2
{

const Phoneme Phoneme::None = Phoneme { };

std::vector<Phoneme> Phoneme::Phonemes;
std::vector<Phoneme::Creator> Phoneme::PrefixHandlers;
std::vector<Phoneme::Modifier> Phoneme::SuffixHandlers;
std::vector<Phoneme::Comparator> Phoneme::Comparators;

Phoneme Phoneme::create(const std::u32string_view s, size_t& i)
{
    Phoneme ret; // Value that we should return

    // This loops for all custom prefix handlers. Handlers should return Phoneme::None
    // if they did not handle the phoneme.
    for (const auto& f : PrefixHandlers) {
        ret = f(s, i);
        if (ret != Phoneme::None) {
            return ret;
        }
    }

    // Search for known phonemes.
    auto iter = std::find_if(Phonemes.cbegin(), Phonemes.cend(), [&s, i](const Phoneme& p) -> bool {
        return s.substr(i, p.String.size()) == p.String;
    });
    // If found, copy; else unknown.
    if (iter != Phonemes.cend()) {
        ret = *iter;
        i += ret.String.size();
    } else {
        ret = Phoneme { s.substr(i++, 1), Phoneme::None.Properties };
    }

    // This loops for all custom suffix handlers. Handlers should return false
    // if they did not handle any suffixes.
    size_t j = 0;
    while (j < SuffixHandlers.size() && i < s.size()) {
        if (SuffixHandlers[j](ret, s, i)) {
            j = 0; // Suffix is handled. Return to start.
        } else {
            ++j; // Suffix is not handled yet. Continue searching.
        }
    } // We are out of the loop once we cannot handle any suffixes.

    return ret;
}

}
