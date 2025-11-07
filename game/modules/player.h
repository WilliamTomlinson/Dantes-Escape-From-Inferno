/**  @file   player.h
     @author W. R. J. Tomlinson
     @date   09 Oct 2025
     @brief  Player instance handler.
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <system.h>
#include "physics.h"


typedef enum {
    WAIT,
    ONGROUND,
    AIRBORNE
} PlayerState_t;

typedef struct {
    uint8_t health;
    uint8_t roundSpeed;
    PlayerState_t state;
    DynamicBody_t body;
} Player_t;

void playerInit(Player_t* player);

void playerReturnToStart(Player_t* player);

void playerJump(Player_t* player);

void playerDeductHealth(Player_t* player, uint8_t penalty);

void playerUpdateMotion(Player_t* player);

void playerStopMotion(Player_t* player);

bool playerBoundaryCheckAndResolver(Player_t* player);

void playerCollisionCheckandResolver(Player_t* player);

bool isPlayerAlive(Player_t* player);

CollisionSide_t playerOnWorldCollisionCheckAndResolve(Player_t* player);

#endif