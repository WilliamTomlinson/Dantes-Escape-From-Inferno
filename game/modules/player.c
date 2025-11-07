/**  @file   player.c
     @author W. R. J. Tomlinson
     @date   09 Oct 2025
     @brief  Player instance handler.
*/

#include "player.h"
#include "math.h"

#define PLAYER_SPEED 1
#define PLAYER_MASS 1
#define PLAYER_JUMP_FORCE 1
#define PLAYER_ROUND_SPEED_SCALE 1
#define PLAYER_STARTING_LIVES 3
#define PLAYER_OUT_OF_BOUNDS_PENALTY 2
#define PLAYER_COLLISION_PENALTY 1
#define PLAYER_SIZE TILE_SIZE_PIXELS
#define PLAYER_START_X_POSITION 24
#define PLAYER_START_Y_POSITION 24

static uint8_t gameRound = 1;

void playerInit(Player_t* player)
{
     gameRound = 1;
     player->health = PLAYER_STARTING_LIVES;
     player->state = AIRBORNE;
     player->roundSpeed = PLAYER_ROUND_SPEED_SCALE;

     DynamicBody_t* dynamicBody = &player->body;
     Vector2D_t* transform = &dynamicBody->transform;
     Vector2D_t* collider = &dynamicBody->collider;
     MassiveBody_t* massBody = &dynamicBody->massBody;
     massiveBodyStopMotion(massBody);

     massBody->mass = PLAYER_MASS;
     transform->x = PLAYER_START_X_POSITION;
     transform->y = PLAYER_START_Y_POSITION;
     collider->x = PLAYER_SIZE / 2;
     collider->y = PLAYER_SIZE / 2;
}


void playerReturnToStart(Player_t* player)
{
     player->state = AIRBORNE;
     player->body.transform.x = PLAYER_START_X_POSITION;
     player->body.transform.y = PLAYER_START_Y_POSITION;
}

void playerDeductHealth(Player_t* player, uint8_t penalty)
{
     player->health -= penalty;
}


void playerJump(Player_t* player)
{
     Vector2D_t jumpVector;
     jumpVector.x = FIXED_ZERO;
     jumpVector.y = PLAYER_JUMP_FORCE;
     massiveBodyApplyForce(&player->body.massBody, jumpVector);
}


void playerUpdateMotion(Player_t* player)
{
     MassiveBody_t* body = &player->body.massBody;
     body->velocity.x = INT_TO_FIXED(PLAYER_ROUND_SPEED_SCALE * gameRound);
     if (player->state != ONGROUND) {
          massiveBodyApplyGForce(body);
     }
     massiveBodyUpdate(body);
     massiveBodyClearNetForce(body);
}

void playerStopMotion(Player_t* player) {
     massiveBodyStopMotion(&player->body.massBody);
}

bool isPlayerAlive(Player_t* player) {
     if (player->health <= 0) {
          return 0;
     }
     return 1;
}