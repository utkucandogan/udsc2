#include <catch2/catch.hpp>

#ifndef UDSC2_SHARED

#include "phoneme.hpp"
#include "procedural.hpp"
#include "v1_0/ipa.hpp"
#include "v1_0/prenasal.hpp"
#include "v1_0/relative_articulation.hpp"

#endif

#ifndef UDSC2_SHARED
namespace udsc2::tests
{

#pragma region Example Phonemes
auto k = Phoneme { U"k", Phoneme::Properties {
        api::TYP_CONSONANT,
        0u,
        api::VOI_VOICELESS,
        api::REL_NORMAL,
        api::HEI_NONE,
        api::BAC_NONE,
        api::ROU_NONE,
        0u,
        api::POA_VELAR,
        api::MOA_STOP,
        0u,
        0u,
        0u,
        nullptr,
        nullptr
    } };

auto a = Phoneme { U"a", Phoneme::Properties {
    api::TYP_VOWEL,
    0u,
    api::VOI_MODAL_VOICED,
    api::REL_NORMAL,
    api::HEI_OPEN,
    api::BAC_FRONT,
    api::ROU_UNROUNDED,
    0u,
    api::POA_NONE,
    api::MOA_NONE,
    0u,
    0u,
    0u,
    nullptr,
    nullptr
} };

auto m = Phoneme { U"m", Phoneme::Properties {
    api::TYP_CONSONANT,
    0u,
    api::VOI_MODAL_VOICED,
    api::REL_NORMAL,
    api::HEI_NONE,
    api::BAC_NONE,
    api::ROU_NONE,
    0u,
    api::POA_BILABIAL,
    api::MOA_NASAL,
    0u,
    0u,
    0u,
    nullptr,
    nullptr
} };

auto b = Phoneme { U"b", Phoneme::Properties {
    api::TYP_CONSONANT,
    0u,
    api::VOI_MODAL_VOICED,
    api::REL_NORMAL,
    api::HEI_NONE,
    api::BAC_NONE,
    api::ROU_NONE,
    0u,
    api::POA_BILABIAL,
    api::MOA_STOP,
    0u,
    0u,
    0u,
    nullptr,
    nullptr
} };

auto t = Phoneme { U"t", Phoneme::Properties {
    api::TYP_CONSONANT,
    0u,
    api::VOI_VOICELESS,
    api::REL_NORMAL,
    api::HEI_NONE,
    api::BAC_NONE,
    api::ROU_NONE,
    0u,
    api::POA_ALVEOLAR,
    api::MOA_STOP,
    0u,
    0u,
    0u,
    nullptr,
    nullptr
} };

auto sh = Phoneme { U"ʃ", Phoneme::Properties {
    api::TYP_CONSONANT,
    0u,
    api::VOI_VOICELESS,
    api::REL_NORMAL,
    api::HEI_NONE,
    api::BAC_NONE,
    api::ROU_NONE,
    0u,
    api::POA_PALATOALVEOLAR,
    api::MOA_SIBILANT | api::MOA_FRICATIVE,
    0u,
    0u,
    0u,
    nullptr,
    nullptr
} };

auto r = Phoneme { U"ɾ", Phoneme::Properties {
    api::TYP_CONSONANT,
    0u,
    api::VOI_MODAL_VOICED,
    api::REL_NORMAL,
    api::HEI_NONE,
    api::BAC_NONE,
    api::ROU_NONE,
    0u,
    api::POA_ALVEOLAR,
    api::MOA_RHOTIC | api::MOA_TAP,
    0u,
    0u,
    0u,
    nullptr,
    nullptr
} };
#pragma endregion

TEST_CASE("Testing phoneme creation.", "[Phoneme::create]")
{
    Phoneme::prefixHandlers.clear();
    Phoneme::suffixHandlers.clear();
    Phoneme::phonemes.clear();

    Procedural::prefixHandlers.clear();
    Procedural::suffixHandlers.clear();

    v1_0::Ipa::register_extension();

    auto text = std::u32string { U"kambatʃaɾ" };
    std::vector<Phoneme> phonemes;

    std::vector<Phoneme> supposedTo {
        k, a, m, b, a, t, sh, a, r
    };

    for (size_t i = 0 ; i < text.size() ; ) {
        phonemes.push_back(udsc2::Phoneme::create(text, i));
    }

    REQUIRE(phonemes.size() == supposedTo.size());

    for (size_t i = 0 ; i < phonemes.size() ; ++i) {
        REQUIRE(phonemes[i] == supposedTo[i]);
    }
}

TEST_CASE("Testing v1_0 phoneme creation.", "[Phoneme::create]")
{
    Phoneme::prefixHandlers.clear();
    Phoneme::suffixHandlers.clear();
    Phoneme::phonemes.clear();

    Procedural::prefixHandlers.clear();
    Procedural::suffixHandlers.clear();

    v1_0::Ipa::register_extension();
    v1_0::Prenasal::register_extension();
    v1_0::RelativeArticulation::register_extension();

    auto text = std::u32string { U"kam̥baⁿtʃaɾ" };
    std::vector<Phoneme> phonemes;

    std::vector<Phoneme> supposedTo {
        k, a, m, b, a, t, sh, a, r
    };

    supposedTo[2].properties.voicing = api::VOI_VOICELESS;
    supposedTo[5].properties.moa |= api::MOA_PRENASAL;

    for (size_t i = 0 ; i < text.size() ; ) {
        phonemes.push_back(udsc2::Phoneme::create(text, i));
    }

    REQUIRE(phonemes.size() == supposedTo.size());

    for (size_t i = 0 ; i < phonemes.size() ; ++i) {
        REQUIRE(phonemes[i] == supposedTo[i]);
    }
}

}
#endif
