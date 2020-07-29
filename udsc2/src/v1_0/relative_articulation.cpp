#include "relative_articulation.hpp"

#include "util/bit.h"
#include "procedural.hpp"

namespace udsc2::v1_0
{

constexpr auto RAISE_BELOW      = U'\u031D';
constexpr auto RAISE_MODIFIER   = U'\u02D4';
constexpr auto LOWER_BELOW      = U'\u031E';
constexpr auto LOWER_MODIFIER   = U'\u02D5';
constexpr auto ADVANCE_BELOW    = U'\u031F';
constexpr auto ADVANCE_MODIFIER = U'\u02D6';
constexpr auto RETRACT_BELOW    = U'\u0320';
constexpr auto RETRACT_MODIFIER = U'\u02D7';
constexpr auto VOICELESS_BELOW  = U'\u0325';
constexpr auto VOICELESS_ABOVE  = U'\u030A';
constexpr auto CENTERALIZE      = U'\u0308';
constexpr auto MID_CENTERALIZE  = U'\u033D';


const std::array<char32_t, 10> RelativeArticulation::deepGlyphs = {
    RAISE_BELOW,
    LOWER_BELOW,
    ADVANCE_BELOW,
    RETRACT_BELOW,
};

const std::array<std::pair<char32_t, char32_t>, 4> RelativeArticulation::modifierPairs = {
    std::make_pair(ADVANCE_MODIFIER, ADVANCE_BELOW),
    std::make_pair(RETRACT_MODIFIER, RETRACT_BELOW),
    std::make_pair(RAISE_MODIFIER, RAISE_BELOW),
    std::make_pair(LOWER_MODIFIER, LOWER_BELOW)
};

bool RelativeArticulation::modifier(Phoneme& p, const std::u32string_view s, size_t& i)
{
    switch (s[i]) {
    case VOICELESS_BELOW:
    case VOICELESS_ABOVE:
        if (p.properties.voicing != api::VOI_MODAL_VOICED) {
            return false;
        }
        p.properties.voicing = api::VOI_VOICELESS;
        break;

    case RAISE_BELOW:
    case RAISE_MODIFIER:
        if (raise(p.properties)) {
            break;
        }
        return false;

    case LOWER_BELOW:
    case LOWER_MODIFIER:
        if (lower(p.properties)) {
            break;
        }
        return false;

    case ADVANCE_BELOW:
    case ADVANCE_MODIFIER:
        if (advance(p.properties)) {
            break;
        }
        return false;

    case RETRACT_BELOW:
    case RETRACT_MODIFIER:
        if (retract(p.properties)) {
            break;
        }
        return false;

    case CENTERALIZE:
        if (centeralize(p.properties)) {
            break;
        }
        return false;

    case MID_CENTERALIZE:
        if (midcenteralize(p.properties)) {
            break;
        }
        return false;

    default:
        return false;
    }

    p.string += s[i++];
    return true;
}

bool RelativeArticulation::procedural_modifier(Phoneme& p, const Phoneme::Properties example, const Phoneme::Properties ignore, size_t maxLength)
{
    if (p.properties.voicing == api::VOI_MODAL_VOICED && example.voicing == api::VOI_VOICELESS) {
        p.properties.voicing = api::VOI_VOICELESS;
        if (std::find(deepGlyphs.cbegin(), deepGlyphs.cend(), p.string.back()) != deepGlyphs.cend()) {
            p.string += VOICELESS_ABOVE;
        } else {
            p.string += VOICELESS_BELOW;
        }
        return true;
    }

    int diff  = phoneme_difference(p.properties, example, ignore);

    auto temp = p.properties;
    midcenteralize(temp);
    if (phoneme_difference(temp, example, ignore) < diff) {
        p.properties = temp;
        if (p.string.back() == VOICELESS_ABOVE) {
            p.string.back() = MID_CENTERALIZE;
            p.string += VOICELESS_ABOVE;
        } else {
            p.string += MID_CENTERALIZE;
        }
        return true;
    }

    temp = p.properties;
    midcenteralize(temp);
    if (phoneme_difference(temp, example, ignore) < diff) {
        p.properties = temp;
        if (p.string.back() == VOICELESS_ABOVE) {
            p.string.back() = CENTERALIZE;
            p.string += VOICELESS_ABOVE;
        } else {
            p.string += CENTERALIZE;
        }
        return true;
    }

    // Lambda for abstracting appending logic for diacritics with modifier variants.
    const auto appender = [&p](const char32_t modifier, const char32_t below) {
        auto iter = std::find_if(modifierPairs.cbegin(), modifierPairs.cend(), [&p](std::pair<char32_t, char32_t> pair) {
            return pair.first == p.string.back();
        });
        if (iter != modifierPairs.cend()) {
            p.string.back() = iter->second;
            p.string += modifier;
        } else if (p.string.back() == VOICELESS_BELOW) {
            p.string.back() = VOICELESS_ABOVE;
            p.string += below;
        } else if (std::find(deepGlyphs.cbegin(), deepGlyphs.cend(), p.string.back()) != deepGlyphs.cend()) {
            p.string += modifier;
        } else {
            p.string += below;
        }
    };

    temp = p.properties;
    advance(temp);
    if (phoneme_difference(temp, example, ignore) < diff) {
        p.properties = temp;
        appender(ADVANCE_MODIFIER, ADVANCE_BELOW);
        return true;
    }

    temp = p.properties;
    retract(temp);
    if (phoneme_difference(temp, example, ignore) < diff) {
        p.properties = temp;
        appender(RETRACT_MODIFIER, RETRACT_BELOW);
        return true;
    }

    temp = p.properties;
    raise(temp);
    if (phoneme_difference(temp, example, ignore) < diff) {
        p.properties = temp;
        appender(RAISE_MODIFIER, RAISE_BELOW);
        return true;
    }

    temp = p.properties;
    lower(temp);
    if (phoneme_difference(temp, example, ignore) < diff) {
        p.properties = temp;
        appender(LOWER_MODIFIER, LOWER_BELOW);
        return true;
    }
    return false;
}

bool RelativeArticulation::register_extension() noexcept
{
    Phoneme::suffixHandlers.push_back(modifier);
    Procedural::suffixHandlers.push_back(procedural_modifier);
    return true;
}

bool RelativeArticulation::raise(Phoneme::Properties& p)
{
    if (p.type == api::TYP_CONSONANT) {
        static constexpr uint16_t mask = api::MOA_STOP
                                       | api::MOA_FRICATIVE
                                       | api::MOA_APPROXIMANT
                                       | api::MOA_FLAP
                                       | api::MOA_TRILL;

        auto temp1 = p.moa & mask;
        auto temp2 = p.moa & ~mask;

        switch (temp1) {
        case api::MOA_APPROXIMANT:
            temp1 = api::MOA_FRICATIVE;
            break;
        case api::MOA_FLAP:
            temp1 = api::MOA_STOP;
            break;
        case api::MOA_TAPPED_FRICATIVE:
            temp1 = api::MOA_FLAP;
            break;
        case api::MOA_TRILL:
            temp1 = api::MOA_TRILLED_FRICATIVE;
            break;
        default:
            return false;
        }

        p.moa = temp1 | temp2;
        return true;
    }

    if (p.type == api::TYP_VOWEL) {
        if (p.height <= api::HEI_CLOSE || p.height > api::HEI_OPEN) {
            return false;
        }
        --p.height;
        return true;
    }

    return false;
}

bool RelativeArticulation::lower(Phoneme::Properties& p)
{
    if (p.type == api::TYP_CONSONANT) {
        static constexpr uint16_t mask = api::MOA_STOP
                                | api::MOA_FRICATIVE
                                | api::MOA_APPROXIMANT
                                | api::MOA_FLAP
                                | api::MOA_TRILL;

        auto temp1 = p.moa & mask;
        auto temp2 = p.moa & ~mask;

        switch (temp1) {
        case api::MOA_FRICATIVE:
            temp1 = api::MOA_APPROXIMANT;
            break;
        case api::MOA_TAP:
            temp1 = api::MOA_TAPPED_FRICATIVE;
            break;
        case api::MOA_TRILLED_FRICATIVE:
            temp1 = api::MOA_TRILL;
            break;
        default:
            return false;
        }

        p.moa = temp1 | temp2;
        return true;
    }

    if (p.type == api::TYP_VOWEL) {
        if (p.height < api::HEI_CLOSE || p.height >= api::HEI_OPEN) {
            return false;
        }
        ++p.height;
        return true;
    }

    return false;
}

bool RelativeArticulation::advance(Phoneme::Properties& p)
{
    if (p.type == api::TYP_CONSONANT) {
        if (util::popcount(p.poa) != 1
            || p.poa == api::POA_RETROFLEX
            || p.poa < api::POA_BILABIAL
            || p.poa >= api::POA_GLOTTAL) {
            return false;
        }
        p.poa <<= 1;
        return true;
    }

    if (p.type == api::TYP_VOWEL) {
        if (p.backness < api::BAC_FRONT || p.backness >= api::BAC_BACK) {
            return false;
        }
        ++p.backness;
        return true;
    }

    return false;
}

bool RelativeArticulation::retract(Phoneme::Properties& p)
{
    if (p.type == api::TYP_CONSONANT) {
        if (util::popcount(p.poa) != 1
            || p.poa == api::POA_RETROFLEX
            || p.poa <= api::POA_BILABIAL
            || p.poa > api::POA_GLOTTAL) {
            return false;
        }
        p.poa >>= 1;
        return true;
    }

    if (p.type == api::TYP_VOWEL) {
        if (p.backness <= api::BAC_FRONT || p.backness > api::BAC_BACK) {
            return false;
        }
        --p.backness;
        return true;
    }

    return false;
}

bool RelativeArticulation::centeralize(Phoneme::Properties& p)
{
    if (p.type == api::TYP_VOWEL) {
        if (p.backness < api::BAC_CENTRAL && p.backness >= api::BAC_FRONT) {
            ++p.height;
            return true;
        }
        if (p.backness > api::BAC_CENTRAL && p.backness <= api::BAC_BACK) {
            --p.height;
            return true;
        }
    }

    return false;
}

bool RelativeArticulation::midcenteralize(Phoneme::Properties& p)
{
    bool ret = centeralize(p);

    if (p.type == api::TYP_VOWEL) {
        if (p.height < api::HEI_MID && p.height >= api::HEI_CLOSE) {
            ++p.height;
            return true;
        }
        if (p.height > api::HEI_MID && p.height <= api::HEI_OPEN) {
            --p.height;
            return true;
        }
    }

    return ret;
}

}
