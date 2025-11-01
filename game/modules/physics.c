/** @file   physics.c
    @author W. R. J. Tomlinson
    @date   09 Oct 2025
    @brief  Module for managing particle physics.
*/

#include "physics.h"

const Fixed_t deltaTime = INT_TO_FIXED(1 / 100);

void applyRigidGForce(RigidBody_t* rigid) {
    rigid->netF.y += INT_TO_FIXED(rigid->m * GRAVITY);
}


void applyRigidForce(RigidBody_t* rigid, Vector2D_t force) {
    rigid->netF.x += force.x;
    rigid->netF.y += force.y;
}


void clearRigidNetForce(RigidBody_t* rigid) {
    rigid->netF.x = FIXED_ZERO;
    rigid->netF.y = FIXED_ZERO;
}


void clearRigidAcceleration(RigidBody_t* rigid)
{
    rigid->a.x = FIXED_ZERO;
    rigid->a.y = FIXED_ZERO;
}


void clearRigidVelocity(RigidBody_t* rigid) {
    rigid->v.x = FIXED_ZERO;
    rigid->v.y = FIXED_ZERO;
}


void updateRigidAcceleration(RigidBody_t* rigid) {
    rigid->a.x = rigid->netF.x / rigid->m;
    rigid->a.y = rigid->netF.y / rigid->m;
}


void updateRigidVelocity(RigidBody_t* rigid) {
    rigid->v.x += rigid->a.x * deltaTime;
    rigid->v.y += rigid->a.y * deltaTime;
}


void updateRigid(RigidBody_t* rigid) {
    updateRigidAcceleration(rigid);
    updateRigidVelocity(rigid);
    clearRigidNetForce(rigid);
}


void stopRigidMotion(RigidBody_t* rigid) {
    clearRigidAcceleration(rigid);
    clearRigidVelocity(rigid);
    clearRigidNetForce(rigid);
}


void dynamicBodyUpdate(DynamicBody_t* body) {
    RigidBody_t* rigid = &body->rigid;
    StaticBody_t* statik = &body->statik;
    updateRigid(rigid);
    statik->transform.x += body->rigid.v.x * deltaTime;
    statik->transform.y += body->rigid.v.y * deltaTime;
}


/**
 * Checks for collision between two square colliders using fixed-point math.
 * @return The side of collision FROM THE PERSPECTIVE OF OBJECT A.
 */
CollisionSide_t collisionCheck(const StaticBody_t* statikA, const StaticBody_t* statikB) {
    // Calculate distance and combined radii using fixed-point operations
    Fixed_t dx = FIXED_SUB(statikA->transform.x, statikB->transform.x);
    Fixed_t dy = FIXED_SUB(statikA->transform.y, statikB->transform.y);

    Fixed_t combinedHalfWidths  = FIXED_ADD(statikA->collider.x, statikB->collider.x);
    Fixed_t combinedHalfHeights = FIXED_ADD(statikA->collider.y, statikB->collider.y);

    // Overlap check using fixed-point comparison and absolute value
    if (FIXED_GT(FIXED_ABS(dx), combinedHalfWidths) || FIXED_GT(FIXED_ABS(dy), combinedHalfHeights)) {
    return COLLISION_NONE;
    }

    // Calculate penetration depth (overlap)
    Fixed_t xOverlap = FIXED_SUB(combinedHalfWidths, FIXED_ABS(dx));
    Fixed_t yOverlap = FIXED_SUB(combinedHalfHeights, FIXED_ABS(dy));

    // Determine the side of collision by the smallest overlap
    if (FIXED_LT(xOverlap, yOverlap)) {
        return (FIXED_GT(dx, FIXED_ZERO)) ? COLLISION_LEFT : COLLISION_RIGHT;
    } else {
        return (FIXED_GT(dy, FIXED_ZERO)) ? COLLISION_BOTTOM : COLLISION_TOP;
    }
}

/**
 * @brief Resolves an AABB collision by moving the dynamic body so it is perfectly
 *        adjacent to the static body on the specified side.
 *
 * @param body1 A pointer to the dynamic body to be moved.
 * @param body2 A pointer to the static body to resolve against.
 * @param side The side of body1 that was hit (e.g., COLLISION_TOP means body2 is at body1's top).
 */
void collisionResolver(StaticBody_t* statikA, const StaticBody_t* statikB, CollisionSide_t side) {
    /* safety check */
    if (side == COLLISION_NONE) {
        return;
    }
    /* initialising useful data */
          Vector2D_t* transformA = &statikA->transform;
    const Vector2D_t* transformB = &statikB->transform;
    const Vector2D_t* colliderA  = &statikA->collider;
    const Vector2D_t* colliderB  = &statikB->collider;

    /* defining for later use */
    Fixed_t combinedHalfWidths;
    Fixed_t combinedHalfHeights;
    
    /* the collision resolver */

    // TODO: this does not work properly

    switch (side) {
        case COLLISION_TOP:
            combinedHalfHeights = FIXED_ADD(colliderA->y, colliderB->y);
            transformA->y = FIXED_ADD(transformB->y, combinedHalfHeights);
            break;
        case COLLISION_BOTTOM:
            combinedHalfHeights = FIXED_ADD(colliderA->y, colliderB->y);
            transformA->y = FIXED_SUB(transformB->y, combinedHalfHeights);
            break;
        case COLLISION_RIGHT:
            combinedHalfWidths = FIXED_ADD(colliderA->x, colliderB->x);
            transformA->x = FIXED_SUB(transformB->x, combinedHalfWidths);
            break;
        case COLLISION_LEFT:
            combinedHalfWidths = FIXED_ADD(colliderA->x, colliderB->x);
            transformA->x = FIXED_ADD(transformB->x, combinedHalfWidths);
            break;
        case COLLISION_NONE:
            break;
    }
}