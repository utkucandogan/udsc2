#pragma once
#ifndef UDSC2_PHONEME_PHONEME_H
#define UDSC2_PHONEME_PHONEME_H

#include <udsc2/internal/export.h>

#include <stdint.h>
#include <uchar.h>

#ifdef __cplusplus
extern "C" {
    namespace udsc2::api
    {
#endif // __cplusplus

    // Phoneme Type
    const uint8_t TYP_NONE               = 0;
    const uint8_t TYP_START              = 1;
    const uint8_t TYP_END                = 2;
    const uint8_t TYP_WHITESPACE         = 3;
    const uint8_t TYP_RESERVED_1         = 4;
    const uint8_t TYP_RESERVED_2         = 5;
    const uint8_t TYP_RESERVED_3         = 6;
    const uint8_t TYP_RESERVED_4         = 7;
    const uint8_t TYP_PHONEME_UNKNOWN    = 8;
    const uint8_t TYP_CONSONANT          = 9;
    const uint8_t TYP_VOWEL              = 10;
    const uint8_t TYP_PHONEME_RESERVED_1 = 11;
    const uint8_t TYP_PHONEME_RESERVED_2 = 12;
    const uint8_t TYP_PHONEME_RESERVED_3 = 13;
    const uint8_t TYP_PHONEME_RESERVED_4 = 14;
    const uint8_t TYP_PHONEME_RESERVED_5 = 15;
    const uint8_t TYP_PRIVATE_USE_1      = 16;
    const uint8_t TYP_PRIVATE_USE_16     = 31;

    // Voicing
    const uint8_t VOI_NONE            = 0;
    const uint8_t VOI_VOICELESS       = 1;
    const uint8_t VOI_BREATHY         = 2;
    const uint8_t VOI_SLACK           = 3;
    const uint8_t VOI_MODAL_VOICED    = 4;
    const uint8_t VOI_STIFF           = 5;
    const uint8_t VOI_CREAKY          = 6;
    const uint8_t VOI_GLOTTAL_CLOSURE = 7;

    // Release
    const uint8_t REL_NORMAL                     = 0;
    const uint8_t REL_NO_AUDIBLE_RELEASE         = 1;
    const uint8_t REL_ASPIRATED                  = 2;
    const uint8_t REL_NASAL                      = 3;
    const uint8_t REL_LATERAL                    = 4;
    const uint8_t REL_VOICELESS_DENTAL_FRICATIVE = 5;
    const uint8_t REL_VOICELESS_VELAR_FRICATIVE  = 6;
    const uint8_t REL_MID_CENTRAL_VOWEL          = 7;

    // Place Of Articulation
    const uint16_t POA_NONE            = 0;
    const uint16_t POA_BILABIAL        = 1 << 0;
    const uint16_t POA_LABIODENTAL     = 1 << 1;
    const uint16_t POA_LINGUOLABIAL    = 1 << 2;
    const uint16_t POA_DENTAL          = 1 << 3;
    const uint16_t POA_ALVEOLAR        = 1 << 4;
    const uint16_t POA_PALATOALVEOLAR  = 1 << 5;
    const uint16_t POA_RETROFLEX       = 1 << 6;
    const uint16_t POA_ALVEOLO_PALATAL = 1 << 7;
    const uint16_t POA_PALATAL         = 1 << 8;
    const uint16_t POA_VELAR           = 1 << 9;
    const uint16_t POA_UVULAR          = 1 << 10;
    const uint16_t POA_PHARYNGEAL      = 1 << 11;
    const uint16_t POA_GLOTTAL         = 1 << 12;
    const uint16_t POA_RESERVED_1      = 1 << 13;
    const uint16_t POA_RESERVED_2      = 1 << 14;
    const uint16_t POA_RESERVED_3      = 1 << 15;

    const uint16_t POA_LABIAL    = POA_BILABIAL
                                 | POA_LABIODENTAL
                                 | POA_LINGUOLABIAL;

    const uint16_t POA_CORONAL   = POA_LINGUOLABIAL
                                 | POA_DENTAL
                                 | POA_ALVEOLAR
                                 | POA_PALATOALVEOLAR
                                 | POA_RETROFLEX
                                 | POA_ALVEOLO_PALATAL;

    const uint16_t POA_DORSAL    = POA_ALVEOLO_PALATAL
                                 | POA_PALATAL
                                 | POA_VELAR
                                 | POA_UVULAR;

    const uint16_t POA_LARYNGEAL = POA_UVULAR
                                 | POA_PHARYNGEAL
                                 | POA_GLOTTAL;

    // Manner Of Articulation
    const uint16_t MOA_NONE        = 0;
    const uint16_t MOA_NASAL       = 1 << 0;
    const uint16_t MOA_STOP        = 1 << 1;
    const uint16_t MOA_FRICATIVE   = 1 << 2;
    const uint16_t MOA_AFFRICATE   = 1 << 3;
    const uint16_t MOA_APPROXIMANT = 1 << 4;
    const uint16_t MOA_TAP         = 1 << 5;
    const uint16_t MOA_TRILL       = 1 << 6;
    const uint16_t MOA_SIBILANT    = 1 << 7;
    const uint16_t MOA_LATERAL     = 1 << 8;
    const uint16_t MOA_LIQUID      = 1 << 9;
    const uint16_t MOA_RHOTIC      = 1 << 10;
    const uint16_t MOA_EJECTIVE    = 1 << 11;
    const uint16_t MOA_IMPLOSIVE   = 1 << 12;
    const uint16_t MOA_CLICK       = 1 << 13;
    const uint16_t MOA_PRENASAL    = 1 << 14;
    const uint16_t MOA_RESERVED_1  = 1 << 15;

    const uint16_t MOA_FLAP              = MOA_TAP;
    const uint16_t MOA_TAPPED_FRICATIVE  = MOA_TAP
                                         | MOA_FRICATIVE;
    const uint16_t MOA_TRILLED_FRICATIVE = MOA_TRILL
                                         | MOA_FRICATIVE;

    // Height, Backness and Roundness
    const uint8_t HEI_NONE       = 0;
    const uint8_t HEI_CLOSE      = 1;
    const uint8_t HEI_NEAR_CLOSE = 2;
    const uint8_t HEI_CLOSE_MID  = 3;
    const uint8_t HEI_MID        = 4;
    const uint8_t HEI_OPEN_MID   = 5;
    const uint8_t HEI_NEAR_OPEN  = 6;
    const uint8_t HEI_OPEN       = 7;

    const uint8_t BAC_NONE       = 0;
    const uint8_t BAC_FRONT      = 1;
    const uint8_t BAC_NEAR_FRONT = 2;
    const uint8_t BAC_CENTRAL    = 3;
    const uint8_t BAC_NEAR_BACK  = 4;
    const uint8_t BAC_BACK       = 5;

    const uint8_t ROU_NONE      = 0;
    const uint8_t ROU_UNROUNDED = 1;
    const uint8_t ROU_RESERVED  = 2;
    const uint8_t ROU_ROUNDED   = 3;

    typedef struct PhonemeProperties // 24-32 Byte
    {
        uint8_t Type       : 5;
        uint8_t Reserved_1 : 3; // 1 Byte
        uint8_t Voicing    : 4;
        uint8_t Release    : 4; // 1 Byte
        uint8_t Height     : 3;
        uint8_t Backness   : 3;
        uint8_t Roundness  : 2; // 1 Byte
        uint8_t Reserved_2;     // 1 Byte
        uint16_t PoA;           // 2 Byte
        uint16_t MoA;           // 2 Byte
        uint16_t Reserved_3;    // 2 Byte
        uint16_t PrivateUse_1;  // 2 Byte
        uint32_t PrivateUse_2;  // 4 Byte
        void* Reserved_4;       // 4-8 Byte
        void* PrivateUse_3;     // 4-8 Byte
    } PhonemeProperties;

    typedef struct Phoneme
    {
        PhonemeProperties Properties;
        const char32_t* String;
    } Phoneme;

    UDSC2_API int phonemeDifference(const api::PhonemeProperties pLeft,
                                    const api::PhonemeProperties pRight,
                                    const api::PhonemeProperties ignore);

#ifdef __cplusplus
    }
}
#endif // __cplusplus

#endif // UDSC2_PHONEME_PHONEME_H
