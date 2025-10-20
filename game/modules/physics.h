/** @file   physics.h
    @author W. R. J. Tomlinson
    @date   09 Oct 2025
    @brief  Module for managing particle physics.
*/

#ifndef PHYSICS_H
#define PHYSICS_H

#include "fixed_math.h"
#include "fixed_vector_2d.h"
#include "simple_vector_2d.h"

#define GRAVITY -10


typedef struct {
    uint8_t mass;
    FixedVector2D_t velocity;
    FixedVector2D_t acceleration;
    FixedVector2D_t netForce;
} MassiveBody_t;


typedef struct {
    FixedVector2D_t transform;
    SimpleVector2D_t collider;
} StaticBody_t;


typedef struct {
    FixedVector2D_t transform;
    SimpleVector2D_t collider;
    MassiveBody_t massBody;
} DynamicBody_t;

typedef enum {
    COLLISION_NONE,
    COLLISION_TOP,
    COLLISION_BOTTOM,
    COLLISION_LEFT,
    COLLISION_RIGHT
} CollisionSide_t;
 

void massiveBodyApplyGForce(MassiveBody_t* body);

void massiveBodyApplyForce(MassiveBody_t* body, FixedVector2D_t force);

void massiveBodyClearNetForce(MassiveBody_t* body);

void massiveBodyUpdateAcceleration(MassiveBody_t* body);

void massiveBodyUpdateVelocity(MassiveBody_t* body);

void massiveBodyUpdate(MassiveBody_t* body);

void massiveBodyStopMotion(MassiveBody_t* body);

void dynamicBodyUpdate(DynamicBody_t* body);

/**
 * Checks for collision between two square colliders using fixed-point math.
 * @return The side of collision FROM THE PERSPECTIVE OF OBJECT A.
 */
CollisionSide_t dynamicOnStaticBodyCollisionCheck(const DynamicBody_t* dynamicBody, const StaticBody_t* staticBody);

/**
 * @brief Resolves an AABB collision by moving the dynamic body so it is perfectly
 *        adjacent to the static body on the specified side.
 *
 * @param body1 A pointer to the dynamic body to be moved.
 * @param body2 A pointer to the static body to resolve against.
 * @param side The side of body1 that was hit (e.g., COLLISION_TOP means body2 is at body1's top).
 */
void dynamicOnStaticBodyResolveCollision(DynamicBody_t* body1, const StaticBody_t* body2, CollisionSide_t side);


#endif /* PHYSICS_H */