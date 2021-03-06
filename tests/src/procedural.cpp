﻿#include <catch2/catch.hpp>

#ifndef UDSC2_SHARED

#include "phoneme.hpp"
#include "procedural.hpp"
#include "v1_0/ipa.hpp"
#include "v1_0/prenasal.hpp"
#include "v1_0/relative_articulation.hpp"
#include "v1_0/tie.hpp"

namespace udsc2::tests
{

TEST_CASE("Testing procedural creation.", "[Procedural::create]")
{
    Phoneme::prefixHandlers.clear();
    Phoneme::suffixHandlers.clear();
    Phoneme::phonemes.clear();

    Procedural::prefixHandlers.clear();
    Procedural::suffixHandlers.clear();

    v1_0::Ipa::register_extension();
    v1_0::Prenasal::register_extension();
    v1_0::RelativeArticulation::register_extension();
    v1_0::Tie::register_extension();

    auto ret = Procedural::generate(Phoneme::Properties {
        api::TYP_CONSONANT,
        0u,
        api::VOI_MODAL_VOICED,
        api::REL_NORMAL,
        api::HEI_NONE,
        api::BAC_NONE,
        api::ROU_NONE,
        0u,
        api::POA_ALVEOLAR,
        api::MOA_STOP | api::MOA_PRENASAL,
        0u,
        0u,
        0u,
        nullptr,
        nullptr
    }, Phoneme::NONE.properties, 5);

    REQUIRE(ret.string == U"ⁿd");

    ret = Procedural::generate(Phoneme::Properties {
        api::TYP_CONSONANT,
        0u,
        api::VOI_MODAL_VOICED,
        api::REL_NORMAL,
        api::HEI_NONE,
        api::BAC_NONE,
        api::ROU_NONE,
        0u,
        api::POA_BILABIAL,
        api::MOA_STOP | api::MOA_PRENASAL,
        0u,
        0u,
        0u,
        nullptr,
        nullptr
    }, Phoneme::NONE.properties, 5);

    REQUIRE(ret.string == U"ᵐb");

    ret = Procedural::generate(Phoneme::Properties {
        api::TYP_CONSONANT,
        0u,
        api::VOI_VOICELESS,
        api::REL_NORMAL,
        api::HEI_NONE,
        api::BAC_NONE,
        api::ROU_NONE,
        0u,
        api::POA_ALVEOLAR,
        api::MOA_TAPPED_FRICATIVE | api::MOA_PRENASAL | api::MOA_RHOTIC,
        0u,
        0u,
        0u,
        nullptr,
        nullptr
    }, Phoneme::NONE.properties, 5);

    REQUIRE(ret.string == U"ⁿɾ̞̊");

    ret = Procedural::generate(Phoneme::Properties {
        api::TYP_CONSONANT,
        0u,
        api::VOI_MODAL_VOICED,
        api::REL_NORMAL,
        api::HEI_NONE,
        api::BAC_NONE,
        api::ROU_NONE,
        0u,
        api::POA_VELAR | api::POA_BILABIAL,
        api::MOA_STOP | api::MOA_PRENASAL,
        0u,
        0u,
        0u,
        nullptr,
        nullptr
    }, Phoneme::NONE.properties, 5);

    REQUIRE(ret.string == U"ᵑᵐɡ͡b");
}

TEST_CASE("Testing tie prenasal procedural creation.", "[Procedural::create]")
{
    Phoneme::prefixHandlers.clear();
    Phoneme::suffixHandlers.clear();
    Phoneme::phonemes.clear();

    Procedural::prefixHandlers.clear();
    Procedural::suffixHandlers.clear();

    v1_0::Ipa::register_extension();
    //v1_0::Prenasal::register_extension();
    v1_0::RelativeArticulation::register_extension();
    v1_0::Tie::register_extension();

    auto ret = Procedural::generate(Phoneme::Properties {
        api::TYP_CONSONANT,
        0u,
        api::VOI_MODAL_VOICED,
        api::REL_NORMAL,
        api::HEI_NONE,
        api::BAC_NONE,
        api::ROU_NONE,
        0u,
        api::POA_ALVEOLAR,
        api::MOA_STOP | api::MOA_PRENASAL,
        0u,
        0u,
        0u,
        nullptr,
        nullptr
    }, Phoneme::NONE.properties, 5);

    REQUIRE(ret.string == U"n͡d");

    ret = Procedural::generate(Phoneme::Properties {
        api::TYP_CONSONANT,
        0u,
        api::VOI_MODAL_VOICED,
        api::REL_NORMAL,
        api::HEI_NONE,
        api::BAC_NONE,
        api::ROU_NONE,
        0u,
        api::POA_BILABIAL,
        api::MOA_STOP | api::MOA_PRENASAL,
        0u,
        0u,
        0u,
        nullptr,
        nullptr
    }, Phoneme::NONE.properties, 5);

    REQUIRE(ret.string == U"m͡b");

    ret = Procedural::generate(Phoneme::Properties {
        api::TYP_CONSONANT,
        0u,
        api::VOI_VOICELESS,
        api::REL_NORMAL,
        api::HEI_NONE,
        api::BAC_NONE,
        api::ROU_NONE,
        0u,
        api::POA_ALVEOLAR,
        api::MOA_TAPPED_FRICATIVE | api::MOA_PRENASAL | api::MOA_RHOTIC,
        0u,
        0u,
        0u,
        nullptr,
        nullptr
    }, Phoneme::NONE.properties, 6);

    REQUIRE(ret.string == U"n͡ɾ̞̊");

    ret = Procedural::generate(Phoneme::Properties {
        api::TYP_CONSONANT,
        0u,
        api::VOI_MODAL_VOICED,
        api::REL_NORMAL,
        api::HEI_NONE,
        api::BAC_NONE,
        api::ROU_NONE,
        0u,
        api::POA_VELAR | api::POA_BILABIAL,
        api::MOA_STOP | api::MOA_PRENASAL,
        0u,
        0u,
        0u,
        nullptr,
        nullptr
    }, Phoneme::NONE.properties, 10);

    REQUIRE(ret.string == U"ŋ͡m͡ɡ͡b");
}

}
#endif
