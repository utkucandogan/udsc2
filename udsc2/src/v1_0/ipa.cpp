#include "ipa.hpp"

#include "phoneme.hpp"

namespace udsc2::v1_0
{

bool Ipa::register_extension()
{
    Phoneme::phonemes.reserve(70 + 31 + Phoneme::phonemes.size());

    Phoneme::phonemes.emplace_back(U"ɴ", api::VOI_MODAL_VOICED , api::POA_UVULAR                      , api::MOA_NASAL                                     );
    Phoneme::phonemes.emplace_back(U"ŋ", api::VOI_MODAL_VOICED , api::POA_VELAR                       , api::MOA_NASAL                                     );
    Phoneme::phonemes.emplace_back(U"ɲ", api::VOI_MODAL_VOICED , api::POA_PALATAL                     , api::MOA_NASAL                                     );
    Phoneme::phonemes.emplace_back(U"ɳ", api::VOI_MODAL_VOICED , api::POA_RETROFLEX                   , api::MOA_NASAL                                     );
    Phoneme::phonemes.emplace_back(U"n", api::VOI_MODAL_VOICED , api::POA_ALVEOLAR                    , api::MOA_NASAL                                     );
    Phoneme::phonemes.emplace_back(U"ɱ", api::VOI_MODAL_VOICED , api::POA_LABIODENTAL                 , api::MOA_NASAL                                     );
    Phoneme::phonemes.emplace_back(U"m", api::VOI_MODAL_VOICED , api::POA_BILABIAL                    , api::MOA_NASAL                                     );

    Phoneme::phonemes.emplace_back(U"q", api::VOI_VOICELESS    , api::POA_UVULAR                      , api::MOA_STOP                                      );
    Phoneme::phonemes.emplace_back(U"ɢ", api::VOI_MODAL_VOICED , api::POA_UVULAR                      , api::MOA_STOP                                      );
    Phoneme::phonemes.emplace_back(U"ʡ", api::VOI_VOICELESS    , api::POA_PHARYNGEAL                  , api::MOA_STOP                                      );
    Phoneme::phonemes.emplace_back(U"ʔ", api::VOI_VOICELESS    , api::POA_GLOTTAL                     , api::MOA_STOP                                      );
    Phoneme::phonemes.emplace_back(U"k", api::VOI_VOICELESS    , api::POA_VELAR                       , api::MOA_STOP                                      );
    Phoneme::phonemes.emplace_back(U"ɡ", api::VOI_MODAL_VOICED , api::POA_VELAR                       , api::MOA_STOP                                      );
    Phoneme::phonemes.emplace_back(U"g", api::VOI_MODAL_VOICED , api::POA_VELAR                       , api::MOA_STOP                                      );
    Phoneme::phonemes.emplace_back(U"c", api::VOI_VOICELESS    , api::POA_PALATAL                     , api::MOA_STOP                                      );
    Phoneme::phonemes.emplace_back(U"ɟ", api::VOI_MODAL_VOICED , api::POA_PALATAL                     , api::MOA_STOP                                      );
    Phoneme::phonemes.emplace_back(U"ʈ", api::VOI_VOICELESS    , api::POA_RETROFLEX                   , api::MOA_STOP                                      );
    Phoneme::phonemes.emplace_back(U"ɖ", api::VOI_MODAL_VOICED , api::POA_RETROFLEX                   , api::MOA_STOP                                      );
    Phoneme::phonemes.emplace_back(U"t", api::VOI_VOICELESS    , api::POA_ALVEOLAR                    , api::MOA_STOP                                      );
    Phoneme::phonemes.emplace_back(U"d", api::VOI_MODAL_VOICED , api::POA_ALVEOLAR                    , api::MOA_STOP                                      );
    Phoneme::phonemes.emplace_back(U"p", api::VOI_VOICELESS    , api::POA_BILABIAL                    , api::MOA_STOP                                      );
    Phoneme::phonemes.emplace_back(U"b", api::VOI_MODAL_VOICED , api::POA_BILABIAL                    , api::MOA_STOP                                      );

    Phoneme::phonemes.emplace_back(U"ɸ", api::VOI_VOICELESS    , api::POA_BILABIAL                    , api::MOA_FRICATIVE                                 );
    Phoneme::phonemes.emplace_back(U"β", api::VOI_MODAL_VOICED , api::POA_BILABIAL                    , api::MOA_FRICATIVE                                 );
    Phoneme::phonemes.emplace_back(U"f", api::VOI_VOICELESS    , api::POA_LABIODENTAL                 , api::MOA_FRICATIVE                                 );
    Phoneme::phonemes.emplace_back(U"v", api::VOI_MODAL_VOICED , api::POA_LABIODENTAL                 , api::MOA_FRICATIVE                                 );
    Phoneme::phonemes.emplace_back(U"θ", api::VOI_VOICELESS    , api::POA_DENTAL                      , api::MOA_FRICATIVE                                 );
    Phoneme::phonemes.emplace_back(U"ð", api::VOI_MODAL_VOICED , api::POA_DENTAL                      , api::MOA_FRICATIVE                                 );
    Phoneme::phonemes.emplace_back(U"s", api::VOI_VOICELESS    , api::POA_ALVEOLAR                    , api::MOA_FRICATIVE | api::MOA_SIBILANT             );
    Phoneme::phonemes.emplace_back(U"z", api::VOI_MODAL_VOICED , api::POA_ALVEOLAR                    , api::MOA_FRICATIVE | api::MOA_SIBILANT             );
    Phoneme::phonemes.emplace_back(U"ʃ", api::VOI_VOICELESS    , api::POA_PALATOALVEOLAR              , api::MOA_FRICATIVE | api::MOA_SIBILANT             );
    Phoneme::phonemes.emplace_back(U"ʒ", api::VOI_MODAL_VOICED , api::POA_PALATOALVEOLAR              , api::MOA_FRICATIVE | api::MOA_SIBILANT             );
    Phoneme::phonemes.emplace_back(U"ʂ", api::VOI_VOICELESS    , api::POA_RETROFLEX                   , api::MOA_FRICATIVE | api::MOA_SIBILANT             );
    Phoneme::phonemes.emplace_back(U"ʐ", api::VOI_MODAL_VOICED , api::POA_RETROFLEX                   , api::MOA_FRICATIVE | api::MOA_SIBILANT             );
    Phoneme::phonemes.emplace_back(U"ɕ", api::VOI_VOICELESS    , api::POA_ALVEOLO_PALATAL             , api::MOA_FRICATIVE | api::MOA_SIBILANT             );
    Phoneme::phonemes.emplace_back(U"ʑ", api::VOI_MODAL_VOICED , api::POA_ALVEOLO_PALATAL             , api::MOA_FRICATIVE | api::MOA_SIBILANT             );
    Phoneme::phonemes.emplace_back(U"ç", api::VOI_VOICELESS    , api::POA_PALATAL                     , api::MOA_FRICATIVE                                 );
    Phoneme::phonemes.emplace_back(U"ʝ", api::VOI_MODAL_VOICED , api::POA_PALATAL                     , api::MOA_FRICATIVE                                 );
    Phoneme::phonemes.emplace_back(U"x", api::VOI_VOICELESS    , api::POA_VELAR                       , api::MOA_FRICATIVE                                 );
    Phoneme::phonemes.emplace_back(U"ɣ", api::VOI_MODAL_VOICED , api::POA_VELAR                       , api::MOA_FRICATIVE                                 );
    Phoneme::phonemes.emplace_back(U"χ", api::VOI_VOICELESS    , api::POA_UVULAR                      , api::MOA_FRICATIVE                                 );
    Phoneme::phonemes.emplace_back(U"ʁ", api::VOI_MODAL_VOICED , api::POA_UVULAR                      , api::MOA_FRICATIVE | api::MOA_RHOTIC               );
    Phoneme::phonemes.emplace_back(U"ħ", api::VOI_VOICELESS    , api::POA_PHARYNGEAL                  , api::MOA_FRICATIVE                                 );
    Phoneme::phonemes.emplace_back(U"ʕ", api::VOI_MODAL_VOICED , api::POA_PHARYNGEAL                  , api::MOA_FRICATIVE                                 );
    Phoneme::phonemes.emplace_back(U"h", api::VOI_VOICELESS    , api::POA_GLOTTAL                     , api::MOA_FRICATIVE                                 );
    Phoneme::phonemes.emplace_back(U"ɦ", api::VOI_MODAL_VOICED , api::POA_GLOTTAL                     , api::MOA_FRICATIVE                                 );

    Phoneme::phonemes.emplace_back(U"ʋ", api::VOI_MODAL_VOICED , api::POA_LABIODENTAL                 , api::MOA_APPROXIMANT                               );
    Phoneme::phonemes.emplace_back(U"ɹ", api::VOI_MODAL_VOICED , api::POA_ALVEOLAR                    , api::MOA_APPROXIMANT | api::MOA_RHOTIC             );
    Phoneme::phonemes.emplace_back(U"ɻ", api::VOI_MODAL_VOICED , api::POA_RETROFLEX                   , api::MOA_APPROXIMANT | api::MOA_RHOTIC             );
    Phoneme::phonemes.emplace_back(U"j", api::VOI_MODAL_VOICED , api::POA_PALATAL                     , api::MOA_APPROXIMANT                               );
    Phoneme::phonemes.emplace_back(U"ɰ", api::VOI_MODAL_VOICED , api::POA_VELAR                       , api::MOA_APPROXIMANT                               );

    Phoneme::phonemes.emplace_back(U"ʙ", api::VOI_MODAL_VOICED , api::POA_BILABIAL                    , api::MOA_TRILL                                     );
    Phoneme::phonemes.emplace_back(U"r", api::VOI_MODAL_VOICED , api::POA_ALVEOLAR                    , api::MOA_TRILL | api::MOA_RHOTIC                   );
    Phoneme::phonemes.emplace_back(U"ʀ", api::VOI_MODAL_VOICED , api::POA_UVULAR                      , api::MOA_TRILL | api::MOA_RHOTIC                   );
    Phoneme::phonemes.emplace_back(U"ʜ", api::VOI_VOICELESS    , api::POA_PHARYNGEAL                  , api::MOA_TRILL                                     );
    Phoneme::phonemes.emplace_back(U"ʢ", api::VOI_MODAL_VOICED , api::POA_PHARYNGEAL                  , api::MOA_TRILL                                     );

    Phoneme::phonemes.emplace_back(U"ⱱ", api::VOI_MODAL_VOICED , api::POA_LABIODENTAL                 , api::MOA_TAP                                       );
    Phoneme::phonemes.emplace_back(U"ɾ", api::VOI_MODAL_VOICED , api::POA_ALVEOLAR                    , api::MOA_TAP | api::MOA_RHOTIC                     );
    Phoneme::phonemes.emplace_back(U"ɽ", api::VOI_MODAL_VOICED , api::POA_RETROFLEX                   , api::MOA_TAP | api::MOA_RHOTIC                     );

    Phoneme::phonemes.emplace_back(U"ɬ", api::VOI_VOICELESS    , api::POA_ALVEOLAR                    , api::MOA_FRICATIVE | api::MOA_LATERAL              );
    Phoneme::phonemes.emplace_back(U"ɮ", api::VOI_MODAL_VOICED , api::POA_ALVEOLAR                    , api::MOA_FRICATIVE | api::MOA_LATERAL              );

    Phoneme::phonemes.emplace_back(U"l", api::VOI_MODAL_VOICED , api::POA_ALVEOLAR                    , api::MOA_APPROXIMANT | api::MOA_LATERAL            );
    Phoneme::phonemes.emplace_back(U"ɫ", api::VOI_MODAL_VOICED , api::POA_ALVEOLAR | api::POA_VELAR   , api::MOA_APPROXIMANT | api::MOA_LATERAL            );
    Phoneme::phonemes.emplace_back(U"ɭ", api::VOI_MODAL_VOICED , api::POA_RETROFLEX                   , api::MOA_APPROXIMANT | api::MOA_LATERAL            );
    Phoneme::phonemes.emplace_back(U"ʎ", api::VOI_MODAL_VOICED , api::POA_PALATAL                     , api::MOA_APPROXIMANT | api::MOA_LATERAL            );
    Phoneme::phonemes.emplace_back(U"ʟ", api::VOI_MODAL_VOICED , api::POA_VELAR                       , api::MOA_APPROXIMANT | api::MOA_LATERAL            );

    Phoneme::phonemes.emplace_back(U"ɺ", api::VOI_MODAL_VOICED , api::POA_ALVEOLAR                    , api::MOA_FLAP | api::MOA_LATERAL | api::MOA_RHOTIC );

    Phoneme::phonemes.emplace_back(U"ʍ", api::VOI_VOICELESS    , api::POA_BILABIAL | api::POA_VELAR   , api::MOA_APPROXIMANT                               );
    Phoneme::phonemes.emplace_back(U"w", api::VOI_MODAL_VOICED , api::POA_BILABIAL | api::POA_VELAR   , api::MOA_APPROXIMANT                               );
    Phoneme::phonemes.emplace_back(U"ɥ", api::VOI_MODAL_VOICED , api::POA_BILABIAL | api::POA_PALATAL , api::MOA_APPROXIMANT                               );


    Phoneme::phonemes.emplace_back(U"i", api::VOI_MODAL_VOICED , api::HEI_CLOSE      , api::BAC_FRONT      , api::ROU_UNROUNDED );
    Phoneme::phonemes.emplace_back(U"y", api::VOI_MODAL_VOICED , api::HEI_CLOSE      , api::BAC_FRONT      , api::ROU_ROUNDED   );
    Phoneme::phonemes.emplace_back(U"ɨ", api::VOI_MODAL_VOICED , api::HEI_CLOSE      , api::BAC_CENTRAL    , api::ROU_UNROUNDED );
    Phoneme::phonemes.emplace_back(U"ʉ", api::VOI_MODAL_VOICED , api::HEI_CLOSE      , api::BAC_CENTRAL    , api::ROU_ROUNDED   );
    Phoneme::phonemes.emplace_back(U"ɯ", api::VOI_MODAL_VOICED , api::HEI_CLOSE      , api::BAC_BACK       , api::ROU_UNROUNDED );
    Phoneme::phonemes.emplace_back(U"u", api::VOI_MODAL_VOICED , api::HEI_CLOSE      , api::BAC_BACK       , api::ROU_ROUNDED   );

    Phoneme::phonemes.emplace_back(U"ɪ", api::VOI_MODAL_VOICED , api::HEI_NEAR_CLOSE , api::BAC_NEAR_FRONT , api::ROU_UNROUNDED );
    Phoneme::phonemes.emplace_back(U"ʏ", api::VOI_MODAL_VOICED , api::HEI_NEAR_CLOSE , api::BAC_NEAR_FRONT , api::ROU_ROUNDED   );
    Phoneme::phonemes.emplace_back(U"ʊ", api::VOI_MODAL_VOICED , api::HEI_NEAR_CLOSE , api::BAC_NEAR_BACK  , api::ROU_ROUNDED   );

    Phoneme::phonemes.emplace_back(U"e", api::VOI_MODAL_VOICED , api::HEI_CLOSE_MID  , api::BAC_FRONT      , api::ROU_UNROUNDED );
    Phoneme::phonemes.emplace_back(U"ø", api::VOI_MODAL_VOICED , api::HEI_CLOSE_MID  , api::BAC_FRONT      , api::ROU_ROUNDED   );
    Phoneme::phonemes.emplace_back(U"ɘ", api::VOI_MODAL_VOICED , api::HEI_CLOSE_MID  , api::BAC_CENTRAL    , api::ROU_UNROUNDED );
    Phoneme::phonemes.emplace_back(U"ɵ", api::VOI_MODAL_VOICED , api::HEI_CLOSE_MID  , api::BAC_CENTRAL    , api::ROU_ROUNDED   );
    Phoneme::phonemes.emplace_back(U"ɤ", api::VOI_MODAL_VOICED , api::HEI_CLOSE_MID  , api::BAC_BACK       , api::ROU_UNROUNDED );
    Phoneme::phonemes.emplace_back(U"o", api::VOI_MODAL_VOICED , api::HEI_CLOSE_MID  , api::BAC_BACK       , api::ROU_ROUNDED   );

    Phoneme::phonemes.emplace_back(U"ə", api::VOI_MODAL_VOICED , api::HEI_MID        , api::BAC_CENTRAL    , api::ROU_UNROUNDED );

    Phoneme::phonemes.emplace_back(U"ɛ", api::VOI_MODAL_VOICED , api::HEI_OPEN_MID   , api::BAC_FRONT      , api::ROU_UNROUNDED );
    Phoneme::phonemes.emplace_back(U"œ", api::VOI_MODAL_VOICED , api::HEI_OPEN_MID   , api::BAC_FRONT      , api::ROU_ROUNDED   );
    Phoneme::phonemes.emplace_back(U"ɜ", api::VOI_MODAL_VOICED , api::HEI_OPEN_MID   , api::BAC_CENTRAL    , api::ROU_UNROUNDED );
    Phoneme::phonemes.emplace_back(U"ɞ", api::VOI_MODAL_VOICED , api::HEI_OPEN_MID   , api::BAC_CENTRAL    , api::ROU_ROUNDED   );
    Phoneme::phonemes.emplace_back(U"ʌ", api::VOI_MODAL_VOICED , api::HEI_OPEN_MID   , api::BAC_BACK       , api::ROU_UNROUNDED );
    Phoneme::phonemes.emplace_back(U"ɔ", api::VOI_MODAL_VOICED , api::HEI_OPEN_MID   , api::BAC_BACK       , api::ROU_ROUNDED   );

    Phoneme::phonemes.emplace_back(U"æ", api::VOI_MODAL_VOICED , api::HEI_NEAR_OPEN  , api::BAC_FRONT      , api::ROU_UNROUNDED );
    Phoneme::phonemes.emplace_back(U"ɐ", api::VOI_MODAL_VOICED , api::HEI_NEAR_OPEN  , api::BAC_CENTRAL    , api::ROU_UNROUNDED );

    Phoneme::phonemes.emplace_back(U"a" ,api::VOI_MODAL_VOICED , api::HEI_OPEN      , api::BAC_FRONT      , api::ROU_UNROUNDED );
    Phoneme::phonemes.emplace_back(U"ɶ" ,api::VOI_MODAL_VOICED , api::HEI_OPEN      , api::BAC_FRONT      , api::ROU_ROUNDED   );
    Phoneme::phonemes.emplace_back(U"ä" ,api::VOI_MODAL_VOICED , api::HEI_OPEN      , api::BAC_CENTRAL    , api::ROU_UNROUNDED );
    Phoneme::phonemes.emplace_back(U"ä" ,api::VOI_MODAL_VOICED , api::HEI_OPEN      , api::BAC_CENTRAL    , api::ROU_UNROUNDED );
    Phoneme::phonemes.emplace_back(U"ɒ̈",api::VOI_MODAL_VOICED , api::HEI_OPEN      , api::BAC_CENTRAL    , api::ROU_ROUNDED   );
    Phoneme::phonemes.emplace_back(U"ɑ" ,api::VOI_MODAL_VOICED , api::HEI_OPEN      , api::BAC_BACK       , api::ROU_UNROUNDED );
    Phoneme::phonemes.emplace_back(U"ɒ" ,api::VOI_MODAL_VOICED , api::HEI_OPEN      , api::BAC_BACK       , api::ROU_ROUNDED   );

    return true;
}

}
