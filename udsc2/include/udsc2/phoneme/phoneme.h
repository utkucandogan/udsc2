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
    enum TYP
    {
        TYP_NONE               = 0,
        TYP_START              = 1,
        TYP_END                = 2,
        TYP_WHITESPACE         = 3,
        TYP_RESERVED_1         = 4,
        TYP_RESERVED_2         = 5,
        TYP_RESERVED_3         = 6,
        TYP_RESERVED_4         = 7,
        TYP_PHONEME_UNKNOWN    = 8,
        TYP_CONSONANT          = 9,
        TYP_VOWEL              = 10,
        TYP_PHONEME_RESERVED_1 = 11,
        TYP_PHONEME_RESERVED_2 = 12,
        TYP_PHONEME_RESERVED_3 = 13,
        TYP_PHONEME_RESERVED_4 = 14,
        TYP_PHONEME_RESERVED_5 = 15,
        TYP_PRIVATE_USE_1      = 16,
        TYP_PRIVATE_USE_16     = 31
    };

    // Voicing
    enum VOI
    {
        VOI_NONE            = 0,
        VOI_VOICELESS       = 1,
        VOI_BREATHY         = 2,
        VOI_SLACK           = 3,
        VOI_MODAL_VOICED    = 4,
        VOI_STIFF           = 5,
        VOI_CREAKY          = 6,
        VOI_GLOTTAL_CLOSURE = 7
    };

    // Release
    enum REL
    {
        REL_NORMAL                     = 0,
        REL_NO_AUDIBLE_RELEASE         = 1,
        REL_ASPIRATED                  = 2,
        REL_NASAL                      = 3,
        REL_LATERAL                    = 4,
        REL_VOICELESS_DENTAL_FRICATIVE = 5,
        REL_VOICELESS_VELAR_FRICATIVE  = 6,
        REL_MID_CENTRAL_VOWEL          = 7
    };

    // Place Of Articulation
    enum POA
    {
        POA_NONE            = 0,
        POA_BILABIAL        = 1 << 0,
        POA_LABIODENTAL     = 1 << 1,
        POA_LINGUOLABIAL    = 1 << 2,
        POA_DENTAL          = 1 << 3,
        POA_ALVEOLAR        = 1 << 4,
        POA_PALATOALVEOLAR  = 1 << 5,
        POA_RETROFLEX       = 1 << 6,
        POA_ALVEOLO_PALATAL = 1 << 7,
        POA_PALATAL         = 1 << 8,
        POA_VELAR           = 1 << 9,
        POA_UVULAR          = 1 << 10,
        POA_PHARYNGEAL      = 1 << 11,
        POA_GLOTTAL         = 1 << 12,
        POA_RESERVED_1      = 1 << 13,
        POA_RESERVED_2      = 1 << 14,
        POA_RESERVED_3      = 1 << 15,

        POA_LABIAL    = POA_BILABIAL
                      | POA_LABIODENTAL
                      | POA_LINGUOLABIAL,

        POA_CORONAL   = POA_LINGUOLABIAL
                      | POA_DENTAL
                      | POA_ALVEOLAR
                      | POA_PALATOALVEOLAR
                      | POA_RETROFLEX
                      | POA_ALVEOLO_PALATAL,

        POA_DORSAL    = POA_ALVEOLO_PALATAL
                      | POA_PALATAL
                      | POA_VELAR
                      | POA_UVULAR,

        POA_LARYNGEAL = POA_UVULAR
                      | POA_PHARYNGEAL
                      | POA_GLOTTAL
    };

    // Manner Of Articulation
    enum MOA
    {
        MOA_NONE        = 0,
        MOA_NASAL       = 1 << 0,
        MOA_STOP        = 1 << 1,
        MOA_FRICATIVE   = 1 << 2,
        MOA_AFFRICATE   = 1 << 3,
        MOA_APPROXIMANT = 1 << 4,
        MOA_TAP         = 1 << 5,
        MOA_TRILL       = 1 << 6,
        MOA_SIBILANT    = 1 << 7,
        MOA_LATERAL     = 1 << 8,
        MOA_LIQUID      = 1 << 9,
        MOA_RHOTIC      = 1 << 10,
        MOA_EJECTIVE    = 1 << 11,
        MOA_IMPLOSIVE   = 1 << 12,
        MOA_CLICK       = 1 << 13,
        MOA_PRENASAL    = 1 << 14,
        MOA_RESERVED_1  = 1 << 15,

        MOA_FLAP              = MOA_TAP,
        MOA_TAPPED_FRICATIVE  = MOA_TAP
                              | MOA_FRICATIVE,
        MOA_TRILLED_FRICATIVE = MOA_TRILL
                              | MOA_FRICATIVE,
    };

    // Height, Backness and Roundness
    enum HEI
    {
        HEI_NONE       = 0,
        HEI_CLOSE      = 1,
        HEI_NEAR_CLOSE = 2,
        HEI_CLOSE_MID  = 3,
        HEI_MID        = 4,
        HEI_OPEN_MID   = 5,
        HEI_NEAR_OPEN  = 6,
        HEI_OPEN       = 7
    };

    enum BAC
    {
        BAC_NONE       = 0,
        BAC_FRONT      = 1,
        BAC_NEAR_FRONT = 2,
        BAC_CENTRAL    = 3,
        BAC_NEAR_BACK  = 4,
        BAC_BACK       = 5
    };

    enum ROU
    {
        ROU_NONE      = 0,
        ROU_UNROUNDED = 1,
        ROU_RESERVED  = 2,
        ROU_ROUNDED   = 3
    };

    typedef uint8_t Type;
    typedef uint8_t Voicing;
    typedef uint8_t Release;
    typedef uint8_t Height;
    typedef uint8_t Backness;
    typedef uint8_t Roundness;
    typedef uint16_t PoA;
    typedef uint16_t MoA;

    typedef struct PhonemeProperties
    {                                   // 24-32 Byte
        Type      type       : 5;
        uint8_t   reserved_1 : 3;       // 1 Byte
        Voicing   voicing    : 4;
        Release   release    : 4;       // 1 Byte
        Height    height     : 3;
        Backness  backness   : 3;
        Roundness roundness  : 2;       // 1 Byte
        uint8_t   reserved_2;           // 1 Byte
        PoA       poa;                  // 2 Byte
        MoA       moa;                  // 2 Byte
        uint16_t  reserved_3;           // 2 Byte
        uint16_t  privateUse_1;         // 2 Byte
        uint32_t  privateUse_2;         // 4 Byte
        void*     reserved_4;           // 4-8 Byte
        void*     privateUse_3;         // 4-8 Byte
    } PhonemeProperties;

    typedef struct Phoneme
    {
        PhonemeProperties properties;
        const char32_t* string;
    } Phoneme;

    const PhonemeProperties PHO_NONE = {
        TYP_NONE,
        0u,
        VOI_NONE,
        REL_NORMAL,
        HEI_NONE,
        BAC_NONE,
        ROU_NONE,
        0u,
        POA_NONE,
        MOA_NONE,
        0u,
        0u,
        0u,
        NULL,
        NULL
    };

    UDSC2_API int phoneme_difference(const PhonemeProperties pLeft,
                                     const PhonemeProperties pRight,
                                     const PhonemeProperties ignore);

#ifdef __cplusplus
    }
}
#endif // __cplusplus

#endif // UDSC2_PHONEME_PHONEME_H
