#ifndef TEXTURES_H_
#define TEXTURES_H_

#include "raylib.h"

#define ATLAS_FILENAME         "texture_atlas.bmp"
#define ATLAS_HTEXTURES_SIZE   32
#define ATLAS_LTEXTURES_SIZE   16
#define ATLAS_WIDTH_LTEXTURES  24 
#define ATLAS_HEIGHT_LTEXTURES 20 

#define TEXTURE_SCALE          2.0f

#define TEXTURE_RECT(l, i) \
    /* (Rectangle) */{\
        .x = ((i) % ATLAS_WIDTH_LTEXTURES) * ATLAS_LTEXTURES_SIZE, \
        .y = ((int)((i) / ATLAS_WIDTH_LTEXTURES)) * ATLAS_LTEXTURES_SIZE, \
        .width = ((l) ? ATLAS_LTEXTURES_SIZE : ATLAS_HTEXTURES_SIZE), \
        .height = ((l) ? ATLAS_LTEXTURES_SIZE : ATLAS_HTEXTURES_SIZE), \
    }

// NOTE: Indexes of high textures increment by 2 instead of 1 because the texture
// atlas is defined in terms of low textures so you need to keep the index in terms
// of low textures

// NOTE: System for naming textures:
// DIRECTIONS:
//     1 - right
//     2 - left
//     3 - up
//     4 - down
//
// ENTITIES:
//     C - cman
//     G - ghost
//     GF - frighten ghost
//     GE - ghost eyes
//     GS - scatter ghost
//
// COLORS:
//     R - red
//     B - blue
//     Y - yellow
//     P - pink
//
// WALLS:
//     W1 - wall double
//     W2 - wall single
//     W3 - wall right_angled (ghost house)
//     D  - prefix for door
//
// CORNERS:
//     First number is whether corner is on top or bottom (3 or 4)
//     two directions combined makes up the corner e.g. C32
//     S - prefix for small
//
// ANIMATIONS:
//     A + number
typedef enum {
    // Row 0
    C2_A1       = 0,
    C2_A2 = 2,
    RG2_A1 = 4,
    RG2_A2 = 6,
    RG1_A1 = 8,
    RG1_A2 = 10,
    RG3_A1 = 12,
    RG3_A2 = 14,
    RG4_A1 = 16,
    RG4_A2 = 18,
    GE2 = 20,
    GF_A1 = 22,

    // Row 2
    C1_A1 = 48,
    C1_A2 = 50,
    PG2_A1 = 52,
    PG2_A2 = 54,
    PG1_A1 = 56,
    PG1_A2 = 58,
    PG3_A1 = 60,
    PG3_A2 = 62,
    PG4_A1 = 64,
    PG4_A2 = 66,
    GE1 = 68,
    GF_A2 = 70,

    // Row 4
    C3_A1 = 96,
    C3_A2 = 98,
    BG2_A1 = 100,
    BG2_A2 = 102,
    BG1_A1 = 104,
    BG1_A2 = 106,
    BG3_A1 = 108,
    BG3_A2 = 110,
    BG4_A1 = 112,
    BG4_A2 = 114,
    GE3 = 116,
    GS_A1 = 118,

    // Row 6
    C4_A1 = 144,
    C4_A2 = 146,
    YG2_A1 = 148,
    YG2_A2 = 150,
    YG1_A1 = 152,
    YG1_A2 = 154,
    YG3_A1 = 156,
    YG3_A2 = 158,
    YG4_A1 = 160,
    YG4_A2 = 162,
    GE4 = 164,
    GS_A2 = 166, 

    // Row 7
    DOT = 192,
    ENERGIZER,

    // Row 8
    W1_1 = 216,
    W1_2,
    W1_3,
    W1_4,
    W1_C31,
    W1_C32,
    W1_C41,
    W1_C42,
    W1_S_C31,
    W1_S_C32,
    W1_S_C41,
    W1_S_C42,

    // Row 9
    W2_1 = 240,
    W2_2,
    W2_3,
    W2_4,
    W2_S_C31,
    W2_S_C32,
    W2_S_C41,
    W2_S_C42,
    W2_C31,
    W2_C32,
    W2_C41,
    W2_C42,
    W2_1_C41,
    W2_1_C31,
    W2_3_C32,
    W2_3_C31,
    W2_2_C32,
    W2_2_C42,

    // Row 10
    W3_1 = 264,
    W3_2,
    W3_3,
    W3_4,
    W3_C31,
    W3_C32,
    W3_C41,
    W3_C42,
    W3_D1,
    W3_D2,
    EMPTY,
} texture_id_t;

extern Rectangle textures[ATLAS_WIDTH_LTEXTURES * ATLAS_HEIGHT_LTEXTURES];
extern Texture2D atlas;

#endif /* TEXTURES_H_ */
