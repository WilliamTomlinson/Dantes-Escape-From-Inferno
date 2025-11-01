/** @file   level.h
    @author W. R. J. Tomlinson
    @date   13 Oct 2025
    @brief  Level creation and storage.
*/


#ifndef LEVEL_H
#define LEVEL_H

#define LEVEL_GRID_HEIGHT 5
#define MAX_LEVEL_LENGTH 32
#define NUMBER_OF_LEVELS 1

#include <stdint.h>

typedef struct {
    uint8_t number;
    const char* description;
    const uint8_t* bitMap;
    uint8_t levelLength;
} Level_t;

extern const Level_t* levels[NUMBER_OF_LEVELS];

#endif /* LEVEL_H */