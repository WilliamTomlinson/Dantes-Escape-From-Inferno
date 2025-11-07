/**  @file   player.c
     @author W. R. J. Tomlinson
     @date   09 Oct 2025
     @brief  Player instance handler.
*/

#include "player.h"
#include "math.h"
#include "physics.h"

/* REQUIRES FINE TUNING ON WORKING BUILD */
#define PLAYER_SPEED 1
#define PLAYER_MASS 1
#define PLAYER_JUMP_FORCE 1
#define PLAYER_ROUND_SPEED_SCALE 1

/* Change these to alter dificulty */
#define PLAYER_STARTING_LIVES 3
#define PLAYER_OUT_OF_BOUNDS_PENALTY 2
#define PLAYER_COLLISION_PENALTY 1

/* Starting positions */
#define PLAYER_START_X_POSITION 24
#define PLAYER_START_Y_POSITION 24

/* Player size */
#define PLAYER_HEIGHT 8
#define PLAYER_WIDTH  8

void playerInit(Player_t* player)
{
     /* Setting player health and state */
     player->health = PLAYER_STARTING_LIVES;
     player->state  = WAIT;

     /* Getting pointers to player body structs */
     StaticBody_t* statik = &player->body.statik;
     RigidBody_t*  rigid  = &player->body.rigid;

     /* Initialises rigid body component */
     rigid->m = PLAYER_MASS;
     stopRigidMotion(rigid);

     /* Initialises static body component */
     Vector2D_t* transform = &statik->transform;
     Vector2D_t* collider  = &statik->collider;

     transform->x = PLAYER_START_X_POSITION;
     transform->y = PLAYER_START_Y_POSITION;
     collider->x  = PLAYER_WIDTH  / 2;
     collider->y  = PLAYER_HEIGHT / 2;
}


void playerReturnToStart(Player_t* player) {
     /* Sets to airborne state to avoid potential odd behavior*/
     player->state = AIRBORNE;
     player->body.statik.transform.x = PLAYER_START_X_POSITION;
     player->body.statik.transform.y = PLAYER_START_Y_POSITION;
}

void playerDeductHealth(Player_t* player, uint8_t penalty) {
     player->health -= penalty;
}

void playerStopMotion(Player_t* player) {
     stopRigidMotion(&player->body.rigid);
}

void playerJump(Player_t* player) {
     Vector2D_t jumpVector;
     jumpVector.x = FIXED_ZERO;
     jumpVector.y = PLAYER_JUMP_FORCE;
     applyForce(&player->body.rigid, jumpVector);
}

void playerSetXVelocity(Player_t* player, Fixed_t v) {
     player->body.rigid.v.x = v;
}


void playerUpdateMotion(Player_t* player) {
     DynamicBody_t* body = &player->body;

     /* WARNING: This statement could lead to bugs (but I like it) 
        this should potentially be it's own function */
     if (player->state != ONGROUND) {
          applyGForce(&body->rigid);
     }
     /* Runs the dynamic body update routine */
     updateDynamic(body);
}


bool isPlayerAlive(Player_t* player) {
     if (player->health <= 0) {
          return 0;
     }
     return 1;
}

void playerDeath(Player_t player) {

}

void playerRespawn(Player_t player) {

}

void playerExceedLeftBound(Player_t player) {

}

void playerExceedRightBound(Player_t player) {

}

void playerExceedTopBound(Player_t player) {

}

void playerExceedBottomBound(Player_t player) {

}

void playerLeftCollision(Player_t player) {

}

void playerRightCollision(Player_t player) {

}

void playerTopCollision(Player_t player) {

}

void playerBottomCollision(Player_t player) {

}

