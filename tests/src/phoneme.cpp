#include <catch2/catch.hpp>

#ifndef UDSC2_SHARED

#include "phoneme.hpp"

#endif

#ifndef UDSC2_SHARED
namespace udsc2::tests
{

TEST_CASE("Testing phoneme creation without ipa.", "[Phoneme::create]")
{
    Phoneme::PrefixHandlers.clear();
    Phoneme::SuffixHandlers.clear();
    Phoneme::Phonemes.clear();

    auto k = Phoneme { U"k", api::PhonemeProperties {
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

    auto a = Phoneme { U"a", api::PhonemeProperties {
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

    auto m = Phoneme { U"m", api::PhonemeProperties {
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

    auto b = Phoneme { U"b", api::PhonemeProperties {
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

    auto t = Phoneme { U"t", api::PhonemeProperties {
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

    auto sh = Phoneme { U"ʃ", api::PhonemeProperties {
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

    auto r = Phoneme { U"ɾ", api::PhonemeProperties {
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

    Phoneme::Phonemes.push_back(k);
    Phoneme::Phonemes.push_back(a);
    Phoneme::Phonemes.push_back(m);
    Phoneme::Phonemes.push_back(b);
    Phoneme::Phonemes.push_back(t);
    Phoneme::Phonemes.push_back(sh);
    Phoneme::Phonemes.push_back(r);


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
