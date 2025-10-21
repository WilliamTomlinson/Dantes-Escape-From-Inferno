/**  @file    world.h
     @authors W. R. J. Tomlinson
     @date    14/10/2025
     @brief   Manages world spatial boundaries, level construction, and static/dynamic body collision logic.
*/

#ifndef WORLD_H
#define WORLD_H

#include "level.h" /* Includes Level_t definition */ 
#include "physics.h"
#include "math.h"

#define MAX_STATIC_BODIES 32
#define TILE_SIZE_PIXELS 8


typedef enum {
    IN_BOUNDS = 0,
    EXCEEDING_TOP_BOUND,
    EXCEEDING_BOTTOM_BOUND,
    EXCEEDING_LEFT_BOUND,
    EXCEEDING_RIGHT_BOUND
} BoundViolation_t;

extern StaticBody_t* levelGrid[LEVEL_GRID_HEIGHT][MAX_LEVEL_LENGTH];

const Level_t* returnCurrentLevel(void);

void worldLoadLevel(const Level_t* levelData);

uint8_t worldToGridIndex(Fixed_t worldCoord);

bool dynamicBodyBottomBoundaryViolationCheck(const DynamicBody_t* body);

bool dynamicBodyTopBoundaryViolationCheck(const DynamicBody_t* body);

bool dynamicBodyLeftBoundaryViolationCheck(const DynamicBody_t* body);

bool dynamicBodyRightBoundaryViolationCheck(const DynamicBody_t* body);

#endif /* WORLD_H */