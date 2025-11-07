/**  @file    world.c
     @authors W. R. J. Tomlinson
     @date    14/10/2025
     @brief   Manages world spatial boundaries, level construction, and static/dynamic body collision logic.
*/


#include "world.h"
#include "physics.h"

static Fixed_t worldEdgeTop;
static Fixed_t worldEdgeBottom = FIXED_ZERO;
static Fixed_t worldEdgeLeft = FIXED_ZERO;
static Fixed_t worldEdgeRight;

static DynamicBody_t* currentPlayer;
static const Level_t* currentLevel;


void worldLoadLevel(const Level_t* levelData, Player_t* playerPointer)
{
    currentPlayer = &playerPointer->body;
    currentLevel = levelData;
    worldEdgeTop = INT_TO_FIXED(levelData->levelLength * TILE_SIZE_PIXELS);
    worldEdgeRight = INT_TO_FIXED(levelData->levelLength * TILE_SIZE_PIXELS);
}


static uint8_t worldToGridIndex(const Fixed_t worldCoord) 
{
    const Fixed_t tileSizeFixed = INT_TO_FIXED(TILE_SIZE_PIXELS);
    return FIXED_TO_INT_TRUNC(FIXED_DIV(worldCoord, tileSizeFixed));
}


bool bottomBoundaryViolationCheck(void) {
    StaticBody_t* statik = &currentPlayer->statik;
    Fixed_t yPos = FIXED_ADD(statik->transform.y, statik->collider.y);
    Fixed_t yMin = FIXED_SUB(yPos, statik->collider.y);
    return FIXED_LT(yMin, worldEdgeBottom);
}


bool topBoundaryViolationCheck(void) {
    StaticBody_t* statik = &currentPlayer->statik;
    Fixed_t yPos = FIXED_ADD(statik->transform.y, statik->collider.y);
    Fixed_t yMax = FIXED_ADD(yPos, statik->collider.y);
    return FIXED_GT(yMax, worldEdgeTop);
}


bool leftBoundaryViolationCheck(void) {
    StaticBody_t* statik = &currentPlayer->statik;
    Fixed_t xPos = FIXED_ADD(statik->transform.x, statik->collider.x);
    Fixed_t xMin = FIXED_SUB(xPos, statik->collider.x);
    return FIXED_LT(xMin, worldEdgeLeft);
}


bool rightBoundaryViolationCheck(void) {
    StaticBody_t* statik = &currentPlayer->statik;
    Fixed_t xPos = FIXED_ADD(statik->transform.x, statik->collider.x);
    Fixed_t xMax = FIXED_ADD(xPos, statik->collider.x);
    return FIXED_GT(xMax, worldEdgeLeft);
}


BoundViolation_t getBoundaryViolation(void) {    
    /* Gets all collision states */
    bool bottom = bottomBoundaryViolationCheck();
    bool top    = topBoundaryViolationCheck();
    bool left   = leftBoundaryViolationCheck();
    bool right  = rightBoundaryViolationCheck();

    /* In order of presidence returns boundary violation */
    if (right) {
        return RIGHT_VIOLATION;
    } else if (bottom) {
        return BOTTOM_VIOLATION;
    } else if (left) {
        return LEFT_VIOLATION;
    } else if (top) {
        return TOP_VIOLATION;
    }

    /* Returns if there are no violations*/
    return NO_VIOLATION;
}


bool boundaryViolationResovle(BoundViolation_t violation) {
    /* Evaluates each case */
    switch (violation) {
        case (LEFT_VIOLATION):
            // todo: right violation update
            // move back into bounds
            break;
        case (RIGHT_VIOLATION):
            // todo: left violation update
            // start a new round
            break;
        case (BOTTOM_VIOLATION):
            // todo: bottom violation update
            // kill player
            break;
        case (TOP_VIOLATION):
            // todo: top violation update
            // do nothing
            break;
        case (NO_VIOLATION):
            return false;
    }
    return true;
}


void platformCollisionResolve(CollisionSide_t side) {
    /* Evaluates each case */
    switch (side) {
        case (LEFT_COLLISION):
            // todo: right violation update
            // kill player
            break;
        case (RIGHT_COLLISION):
            // todo: left violation update
            // kill player
            break;
        case (BOTTOM_COLLISION):
            // todo: bottom violation update
            // resolve
            break;
        case (TOP_COLLISION):
            // todo: top violation update
            // kill player
            break;
        case (NO_COLLISION):
            break;
    }

}


void platformCollisionHandler(void) {
    const Level_t* currentLevel = returnCurrentLevel();
    const uint8_t* bitMap = currentLevel->bitMap;

    Vector2D_t* collider  = &currentPlayer->statik.collider;
    Vector2D_t* transform = &currentPlayer->statik.transform;

    uint8_t xStartTile = worldToGridIndex(FIXED_SUB(transform->x, collider->x));
    uint8_t xEndTile   = worldToGridIndex(FIXED_ADD(transform->x, collider->x));
    uint8_t yStartTile = worldToGridIndex(FIXED_SUB(transform->y, collider->y));
    uint8_t yEndTile   = worldToGridIndex(FIXED_ADD(transform->y, collider->y));

    StaticBody_t* tempStatik;
    initBlankStatic(tempStatik);

    for (uint8_t ty = yStartTile; ty <= yEndTile; ty++) {
        for (uint8_t tx = xStartTile; tx <= xEndTile; tx++) {
            if (bitMap[tx] >> ty) {
                tempStatik->transform.x = tx * TILE_SIZE_PIXELS + TILE_SIZE_PIXELS / 2;
                tempStatik->transform.y = ty * TILE_SIZE_PIXELS + TILE_SIZE_PIXELS / 2;
                CollisionSide_t side = collisionCheck(&currentPlayer->statik, tempStatik);
                platformCollisionResolve(side);
            }
        }
    }
}

