/** @file   level.c
    @author W. R. J. Tomlinson
    @date   13 Oct 2025
    @brief  Level creation and storage.
*/

#include "level.h"

/* Defining Level 1 */

static const uint8_t bitMapLevel1[] = {
    0b00001, // 0: Safe ground start
    0b00001, // 1
    0b00001, // 2
    0b00010, // 3: First Platform on Row 1
    0b00010, // 4
    0b00010, // 5
    0b00100, // 6: Second Platform on Row 2
    0b00100, // 7
    0b00100, // 8
    0b00000, // 9: Nothing...
    0b00100, // 10: Third Platform on Row 2
    0b00100, // 11
    0b00100, // 12
    0b00001, // 13: Drop to Row 0
    0b00001, // 14
    0b00010, // 15: Platform on row 1 
    0b00010, // 16
    0b00100, // 17: Platform on Row 2
    0b00100, // 18
    0b00100, // 19
    0b01000, // 20: Platform on Row 3
    0b01000, // 21
    0b00000, // 22: Big gap...
    0b00000, // 23
    0b00001, // 24: Platform on Row 0
    0b00001, // 25
    0b00000, // 26: Gap
    0b00001, // 27: Platform on Row 0
    0b00001, // 28
    0b00010, // 29: Platform on Row 1
    0b00010, // 30
    0b00000, // 31: Gap before looping bit_map
};

static const char descriptionLevel1[] = "The very first Level!";


const Level_t level1 = {
    .number = 1,
    .description = descriptionLevel1,
    .bitMap = bitMapLevel1,
    .levelLength = 32
};

const Level_t* levels[] = {&level1};