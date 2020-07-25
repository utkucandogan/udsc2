#include "procedural.hpp"

#include <numeric>
#include <algorithm>

namespace udsc2
{

std::vector<Procedural::Creator> Procedural::prefixHandlers;
std::vector<Procedural::Modifier> Procedural::suffixHandlers;
int Procedural::maxDifference = 10;

Phoneme Procedural::generate(const Phoneme::Properties example, const Phoneme::Properties ignore, int maxLenght)
{
    if (maxLenght <= 0) {
        return Phoneme::NONE;
    }

    for (const auto& f : prefixHandlers) {
        auto ret = f(example, ignore, maxLenght);
        if (ret != Phoneme::NONE) {
            return ret;
        }
    }

    std::vector<size_t> indexes(Phoneme::phonemes.size());
    std::iota(indexes.begin(), indexes.end(), 0);
    std::sort(indexes.begin(), indexes.end(), [&example, &ignore](size_t a, size_t b) -> bool {
        int diffa = Phoneme::phonemes[a].difference(example, ignore);
        int diffb = Phoneme::phonemes[b].difference(example, ignore);
        if (diffa == diffb) {
            if (Phoneme::phonemes[a].string.size() == Phoneme::phonemes[b].string.size()) {
                return a < b;
            }
            return Phoneme::phonemes[a].string.size() < Phoneme::phonemes[b].string.size();
        }
        return diffa < diffb;
    });

    for (size_t i = 0 ; i < indexes.size() && Phoneme::phonemes[indexes[i]].difference(example, ignore) <= maxDifference ; ++i) {
        Phoneme p = Phoneme::phonemes[indexes[i]];
        size_t j = 0;
        do {
            if (p.difference(example, ignore) == 0) {
                return p;
            }

            if (j >= suffixHandlers.size()) {
                break;
            }

            if (suffixHandlers[j](p, example, ignore, maxLenght)) {
                j = 0;
            } else {
                ++j;
            }
        } while (p.string.size() <= static_cast<size_t> (maxLenght));
    }
    return Phoneme::NONE;
}

}
