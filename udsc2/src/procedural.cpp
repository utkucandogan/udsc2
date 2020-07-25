#include "procedural.hpp"

#include <numeric>
#include <algorithm>

namespace udsc2
{

std::vector<Procedural::Creator> Procedural::PrefixHandlers;
std::vector<Procedural::Modifier> Procedural::SuffixHandlers;
int Procedural::MaxDifference = 10;

Phoneme Procedural::generate(const api::PhonemeProperties example, const api::PhonemeProperties ignore, int maxLenght)
{
    if (maxLenght <= 0) {
        return Phoneme::None;
    }

    for (const auto& f : PrefixHandlers) {
        auto ret = f(example, ignore, maxLenght);
        if (ret != Phoneme::None) {
            return ret;
        }
    }

    std::vector<size_t> indexes(Phoneme::Phonemes.size());
    std::iota(indexes.begin(), indexes.end(), 0);
    std::sort(indexes.begin(), indexes.end(), [&example, &ignore](size_t a, size_t b) -> bool {
        int diffa = Phoneme::Phonemes[a].difference(example, ignore);
        int diffb = Phoneme::Phonemes[b].difference(example, ignore);
        if (diffa == diffb) {
            if (Phoneme::Phonemes[a].String.size() == Phoneme::Phonemes[b].String.size()) {
                return a < b;
            }
            return Phoneme::Phonemes[a].String.size() < Phoneme::Phonemes[b].String.size();
        }
        return diffa < diffb;
    });

    for (size_t i = 0 ; i < indexes.size() && Phoneme::Phonemes[indexes[i]].difference(example, ignore) <= MaxDifference ; ++i) {
        Phoneme p = Phoneme::Phonemes[indexes[i]];
        size_t j = 0;
        do {
            if (p.difference(example, ignore) == 0) {
                return p;
            }

            if (j >= SuffixHandlers.size()) {
                break;
            }

            if (SuffixHandlers[j](p, example, ignore, maxLenght)) {
                j = 0;
            } else {
                ++j;
            }
        } while (p.String.size() <= static_cast<size_t> (maxLenght));
    }
    return Phoneme::None;
}

}
