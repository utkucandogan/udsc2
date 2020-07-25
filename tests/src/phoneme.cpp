#include <catch2/catch.hpp>

#ifndef UDSC2_SHARED

#include "phoneme.hpp"

#endif

#ifndef UDSC2_SHARED
namespace udsc2::tests
{

TEST_CASE("Testing phoneme creation without ipa.", "[Phoneme::create]")
{
    Phoneme::prefixHandlers.clear();
    Phoneme::suffixHandlers.clear();
    Phoneme::phonemes.clear();

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

    Phoneme::phonemes.push_back(k);
    Phoneme::phonemes.push_back(a);
    Phoneme::phonemes.push_back(m);
    Phoneme::phonemes.push_back(b);
    Phoneme::phonemes.push_back(t);
    Phoneme::phonemes.push_back(sh);
    Phoneme::phonemes.push_back(r);

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

TEST_CASE("Testing phoneme creation.", "[Phoneme::create]")
{

}

}
#endif
