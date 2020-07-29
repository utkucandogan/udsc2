#include "prenasal.hpp"

#include "procedural.hpp"

namespace udsc2::v1_0
{

Phoneme Prenasal::creator(const std::u32string_view s, size_t& i)
{
    switch (s[i]) {
    case U'\u207F': // Superscript n
    case U'\u1D50': // Superscript m
    case U'\u1DAF': // Superscript nr
    case U'\u1DAE': // Superscript ny
    case U'\u1D51': // Superscript ng
    {
        char32_t pre = s[i];
        Phoneme ret = Phoneme::create(s, ++i);
        ret.string.insert(0, 1, pre);
        if (ret.properties.type == api::TYP_CONSONANT) {
            ret.properties.moa |= api::MOA_PRENASAL;
            return ret;
        }
    }
    default:
        return Phoneme::NONE;
    }
}

Phoneme Prenasal::procedural_creator(Phoneme::Properties example, Phoneme::Properties ignore, int maxLength)
{
    if (example.type != api::TYP_CONSONANT || !( example.moa & api::MOA_PRENASAL ) ) {
        return Phoneme::NONE;
    }

    example.moa &= ~api::MOA_PRENASAL;
    auto right = Procedural::generate(example, ignore, maxLength - 1);
    if (right == Phoneme::NONE) {
        return Phoneme::NONE;
    }

    int i = 0;
    if (right.properties.poa & api::POA_VELAR) {
        right.string.insert(i++, 1, U'\u1D51'); // ng
    }
    if (right.properties.poa & api::POA_PALATAL) {
        right.string.insert(i++, 1, U'\u1DAE'); // ny
    }
    if (right.properties.poa & api::POA_RETROFLEX) {
        right.string.insert(i++, 1, U'\u1DAF'); // nr
    }
    if (right.properties.poa & (api::POA_PALATOALVEOLAR | api::POA_ALVEOLAR | api::POA_DENTAL)) {
        right.string.insert(i++, 1, U'\u207F'); // n
    }
    if (right.properties.poa & api::POA_BILABIAL) {
        right.string.insert(i++, 1, U'\u1D50'); // m
    }
    if (i == 0) {
        right.string.insert(i++, 1, U'\u207F'); // n
    }

    right.properties.moa |= api::MOA_PRENASAL;
    return right;
}

bool Prenasal::register_extension()
{
    Phoneme::prefixHandlers.push_back(creator);
    Procedural::prefixHandlers.push_back(procedural_creator);
    return true;
}

}
