/** @file   physics.h
    @author W. R. J. Tomlinson
    @date   09 Oct 2025
    @brief  Module for managing particle physics.
*/

#ifndef PHYSICS_H
#define PHYSICS_H

#include "math.h"

#define GRAVITY -10


typedef struct {
    uint8_t m;
    Vector2D_t v;
    Vector2D_t a;
    Vector2D_t netF;
} RigidBody_t;


typedef struct {
    Vector2D_t transform;
    Vector2D_t collider;
} StaticBody_t;


typedef struct {
    StaticBody_t statik;
    RigidBody_t rigid;
} DynamicBody_t;

typedef enum {
    NO_COLLISION,
    BOTTOM_COLLISION,
    TOP_COLLISION,
    LEFT_COLLISION,
    RIGHT_COLLISION
} CollisionSide_t;
 

void applyRigidGForce(RigidBody_t* rigid);

void applyRigidForce(RigidBody_t* rigid, Vector2D_t force);

void clearRigidNetForce(RigidBody_t* rigid);

void updateRigidAcceleration(RigidBody_t* rigid);

void updateRigidVelocity(RigidBody_t* rigid);

void updateRigid(RigidBody_t* rigid);

void stopRigidMotion(RigidBody_t* rigid);

void updateDynamic(DynamicBody_t* dynamic);

/**
 * Checks for collision between two square colliders using fixed-point math.
 * @return The side of collision FROM THE PERSPECTIVE OF OBJECT A.
 */
CollisionSide_t collisionCheck(const StaticBody_t* statikA, const StaticBody_t* statikB);

/**
 * @brief Resolves an AABB collision by moving the dynamic body so it is perfectly
 *        adjacent to the static body on the specified side.
 *
 * @param body1 A pointer to the dynamic body to be moved.
 * @param body2 A pointer to the static body to resolve against.
 * @param side The side of body1 that was hit (e.g., COLLISION_TOP means body2 is at body1's top).
 */
void collisionResolver(StaticBody_t* statikA, const StaticBody_t* statikB, CollisionSide_t side);


#endif /* PHYSICS_H */