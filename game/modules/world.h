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
#include "player.h"

#define MAX_STATIC_BODIES 32
#define TILE_SIZE_PIXELS 8


typedef enum {
    NO_VIOLATION,
    BOTTOM_VIOLATION,
    TOP_VIOLATION,
    LEFT_VIOLATION,
    RIGHT_VIOLATION
} BoundViolation_t;

extern StaticBody_t* levelGrid[LEVEL_GRID_HEIGHT][MAX_LEVEL_LENGTH];

const Level_t* returnCurrentLevel(void);

void worldLoadLevel(const Level_t* levelData, Player_t* playerPointer);

static uint8_t worldToGridIndex(const Fixed_t worldCoord);

bool dynamicBodyBottomBoundaryViolationCheck(const DynamicBody_t* body);

bool dynamicBodyTopBoundaryViolationCheck(const DynamicBody_t* body);

bool dynamicBodyLeftBoundaryViolationCheck(const DynamicBody_t* body);

bool dynamicBodyRightBoundaryViolationCheck(const DynamicBody_t* body);

#endif /* WORLD_H */