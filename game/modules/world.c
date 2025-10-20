/**  @file    world.c
     @authors W. R. J. Tomlinson
     @date    14/10/2025
     @brief   Manages world spatial boundaries, level construction, and static/dynamic body collision logic.
*/


#include "world.h"

static Fixed_t worldEdgeTop;
static Fixed_t worldEdgeBottom = FIXED_ZERO;
static Fixed_t worldEdgeLeft = FIXED_ZERO;
static Fixed_t worldEdgeRight;

static const Level_t* currentLevel;


void worldLoadLevel(const Level_t* levelData)
{
    currentLevel = levelData;
    uint8_t levelLength = levelData->levelLength;
    worldEdgeTop = INT_TO_FIXED(levelLength * TILE_SIZE_PIXELS);
    worldEdgeRight = INT_TO_FIXED(levelLength * TILE_SIZE_PIXELS);
}


uint8_t worldToGridIndex(Fixed_t worldCoord) 
{
    const Fixed_t tileSizeFixed = INT_TO_FIXED(TILE_SIZE_PIXELS);
    return FIXED_TO_INT_TRUNC(FIXED_DIV(worldCoord, tileSizeFixed));
}


bool dynamicBodyBottomBoundaryViolationCheck(const DynamicBody_t* body)
{
    Fixed_t yPos = FIXED_ADD(body->transform.y, body->collider.y);
    Fixed_t yMin = FIXED_SUB(yPos, body->collider.y);
    return FIXED_LT(yMin, worldEdgeBottom);
}


bool dynamicBodyTopBoundaryViolationCheck(const DynamicBody_t* body)
{
    Fixed_t yPos = FIXED_ADD(body->transform.y, body->collider.y);
    Fixed_t yMax = FIXED_ADD(yPos, body->collider.y);
    return FIXED_GT(yMax, worldEdgeTop);
}


bool dynamicBodyLeftBoundaryViolationCheck(const DynamicBody_t* body)
{
    Fixed_t xPos = FIXED_ADD(body->transform.x, body->collider.x);
    Fixed_t xMin = FIXED_SUB(xPos, body->collider.x);
    return FIXED_LT(xMin, worldEdgeLeft);
}


bool dynamicBodyRightBoundaryViolationCheck(const DynamicBody_t* body)
{
    Fixed_t xPos = FIXED_ADD(body->transform.x, body->collider.x);
    Fixed_t xMax = FIXED_ADD(xPos, body->collider.x);
    return FIXED_GT(xMax, worldEdgeLeft);
}


const Level_t* returnCurrentLevel(void)
{
    return currentLevel;
}
