#include "tie.hpp"

#include "procedural.hpp"

namespace udsc2::v1_0
{

constexpr uint16_t alveolarVariances = api::POA_DENTAL
                                     | api::POA_ALVEOLO_PALATAL
                                     | api::POA_RETROFLEX
                                     | api::POA_PALATOALVEOLAR;

constexpr Phoneme::Properties glottalStop = Phoneme::Properties {
    api::TYP_CONSONANT,
    0u,
    api::VOI_VOICELESS,
    api::REL_NORMAL,
    api::HEI_NONE,
    api::BAC_NONE,
    api::ROU_NONE,
    0u,
    api::POA_GLOTTAL,
    api::MOA_STOP,
    0u,
    0u,
    0u,
    nullptr,
    nullptr
};

bool Tie::modifier(Phoneme& p, const std::u32string_view s, size_t& i)
{
    // Check if tie.
    if (s[i] != U'\u0361' && s[i] != U'\u035C') {
        return false;
    }

    // Tie only works for consonants (at least for now)
    if (p.properties.type != api::TYP_CONSONANT) {
        return false;
    }

    // Add tie to left.
    p.string += s[i];

    auto next = Phoneme::create(s, ++i); // get right phoneme.
    if (next.properties.type != api::TYP_CONSONANT) {
        i -= next.string.size() + 1;
        return false;
    }

    combine(p, next);
    return true;
}

Phoneme Tie::procedural_creator(Phoneme::Properties example, Phoneme::Properties ignore, int maxLength)
{
    if (example.type != api::TYP_CONSONANT) {
        return Phoneme::NONE;
    }

    Phoneme left, right;

    if (example.moa & api::MOA_PRENASAL) { // Prenasal handling
        // Glyph for prenasal is just nasal glyph with same place of articulation.
        auto prenasal = example;
        prenasal.voicing = api::VOI_MODAL_VOICED;
        prenasal.moa = api::MOA_NASAL;
        prenasal.release = api::REL_NORMAL; // Release should be normal

        left = Procedural::generate(prenasal, ignore, maxLength);
        if (left == Phoneme::NONE) {
            return Phoneme::NONE;
        }

        // Right side is just the example without prenasal. Prenasality will be added
        // after combination with left.
        example.moa &= ~api::MOA_PRENASAL;
        right = Procedural::generate(example, ignore, maxLength - left.string.size() - 1);
        if (right == Phoneme::NONE) {
            return Phoneme::NONE;
        }
    } else if (example.voicing == api::VOI_GLOTTAL_CLOSURE) { // Glottal Closure handling
        // Get glottal stop symbol for glottal closure marking
        left = Procedural::generate(glottalStop, Phoneme::NONE.properties, maxLength);
        if (left == Phoneme::NONE) {
            return Phoneme::NONE;
        }

        example.voicing = api::VOI_VOICELESS; // Right side uses voiceless symbol
        right = Procedural::generate(example, ignore, maxLength);
        if (right == Phoneme::NONE) {
            return Phoneme::NONE;
        }
    } else {
        return Phoneme::NONE;
    }

    left.string += U'\u0361'; // Add tie symbol
    // No need to check if they are consonant as they must be consonant to be
    // matched with the examples.
    combine(left, right);
    return left;
}

bool Tie::procedural_modifier(Phoneme& p, Phoneme::Properties example, Phoneme::Properties ignore, size_t maxLength)
{
    // Tie does only work for consonants (at least for now)
    if (example.type != api::TYP_CONSONANT || p.properties.type != api::TYP_CONSONANT) {
        return false;
    }

    // If voicings are not the same, co-articulation cannot solve that issue
    // (Except closed glottis case which is handled differently).
    if (p.properties.voicing != example.voicing) {
        return false;
    }

    auto exampleBackup = example; // Backup so that modifications are not permanent

    // If places of articulation are not same then we can take difference to find
    // poa of right phoneme. If they are same this means that we are dealing with
    // (possibly) affricates.
    if (example.poa != p.properties.poa) {
        example.poa &= ~p.properties.poa;
    }

    // We can ignore secondary features like sibilancy(?) or rhoticy for right phoneme.
    constexpr uint16_t mask = api::MOA_SIBILANT
                            | api::MOA_LATERAL
                            | api::MOA_LIQUID
                            | api::MOA_RHOTIC;


    auto ignore_moa = ignore.moa;
    ignore_moa |= p.properties.moa & mask;

    // Only "real" manner of articulation
    auto moa_example  = example.moa & ~mask;
    auto moa_p_masked = p.properties.moa & ~mask;
    // Similarly if manners of articulation are not same, we can take the difference to
    // find moa of right phoneme. If they are same this means that we are dealing with
    // doubly articulated consonants.
    if (moa_example != moa_p_masked) {
        moa_example &= ~moa_p_masked;
        // If we want tapped fricative, it is not ok for just searching tap or fricative.
        // Because this means that left phoneme is fricative or tap respectively which,
        // is not ok. Tie should not convert tap or fricative into tapped fricative.
        if (!( ~example.moa & api::MOA_TAPPED_FRICATIVE ) && ( moa_example & api::MOA_TAPPED_FRICATIVE )) {
            moa_example |= api::MOA_TAPPED_FRICATIVE;
        }

        // Similar case is for trilled fricative
        if (!( ~example.moa & api::MOA_TRILLED_FRICATIVE ) && ( moa_example & api::MOA_TRILLED_FRICATIVE )) {
            moa_example |= api::MOA_TRILLED_FRICATIVE;
        }
    }

    // Re-add "secondary" features like sibilancy(?) or rhoticy that we did not ignore.
    moa_example |= example.moa & ~p.properties.moa & mask;
    example.moa = moa_example; // Recombine with rest.

    // Affricate specific case: Affricates == Stop + Fricative NOT Fricative + Stop
    // Hence if left side is fricative and right side is stop, this is not acceptable.
    if (( p.properties.moa & api::MOA_FRICATIVE ) && ( example.moa & api::MOA_STOP )) {
        return false;
    }

    // If left phoneme does not help with example, we need to stop proceeding.
    ignore.moa |= mask; // Secondary features does not count
    if (phoneme_difference(exampleBackup, example, ignore) == 0) {
        // If left phoneme is an alveolar variance, searching for alveolar at right
        // may be helpful.
        if (p.properties.poa & alveolarVariances) {
            example.poa &= ~alveolarVariances;
            example.poa |= api::POA_ALVEOLAR;
        } else {
            return false;
        }
    }

    // Continue with using previous ignore variables.
    ignore.moa = ignore_moa;

    // Get right phoneme.
    auto right = Procedural::generate(example, ignore, maxLength - p.string.length() - 1);
    if (right == Phoneme::NONE) {
        // We can recheck for alveolar case if we searched for other alveolar variances
        // since phoneme symbols for alveolars have flexible usage.
        if (example.poa & alveolarVariances) {
            example.poa &= ~alveolarVariances; // Lower variances
            example.poa |= api::POA_ALVEOLAR;  // Raise alveolar
            // Try to get again.
            right = Procedural::generate(example, ignore, maxLength - p.string.length() - 1);
            if (right == Phoneme::NONE) {
                // No luck.
                return false;
            }
        } else {
            // There is no other way, return.
            return false;
        }
    }

    p.string += U'\u0361'; // Add tie glyph.
    // Combine two sides to obtain required phoneme.
    combine(p, right);
    return true; // Success.
}

bool Tie::register_extension() noexcept
{
    Phoneme::suffixHandlers.push_back(modifier);
    Procedural::prefixHandlers.push_back(procedural_creator);
    Procedural::suffixHandlers.push_back(procedural_modifier);
    return true;
}

void Tie::combine(Phoneme& left, const Phoneme& right)
{
    if (left.difference(glottalStop, Phoneme::NONE.properties) == 0) {
        left.properties = right.properties;
        left.properties.voicing = api::VOI_GLOTTAL_CLOSURE;
        left.string += right.string;
        return;
    }

    left.properties.voicing = right.properties.voicing;

    left.properties.poa |= right.properties.poa;
    if (left.properties.poa & alveolarVariances) {
        left.properties.poa &= ~api::POA_ALVEOLAR;
    }

    if (left.properties.moa & api::MOA_NASAL && !(right.properties.moa & api::MOA_NASAL)) {
        left.properties.moa &= ~api::MOA_NASAL;
        left.properties.moa |= api::MOA_PRENASAL;
    }
    if (right.properties.moa & api::MOA_TRILL) {
        left.properties.moa &= ~api::MOA_TAP;
    }
    left.properties.moa |= right.properties.moa;

    left.properties.release = right.properties.release;

    left.string += right.string;
}

}
