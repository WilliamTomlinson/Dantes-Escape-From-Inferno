/** @file   physics.c
    @author W. R. J. Tomlinson
    @date   09 Oct 2025
    @brief  Module for managing particle physics.
*/

#include "physics.h"

const Fixed_t deltaTime = INT_TO_FIXED(1 / 100);

void massiveBodyApplyGForce(MassiveBody_t* body)
{
    body->netForce.y += INT_TO_FIXED(body->mass * GRAVITY);
}


void massiveBodyApplyForce(MassiveBody_t* body, Vector2D_t force)
{
    body->netForce.x += force.x;
    body->netForce.y += force.y;
}

void massiveBodyClearNetForce(MassiveBody_t* body)
{
    body->netForce.x = FIXED_ZERO;
    body->netForce.y = FIXED_ZERO;
}

void massiveBodyUpdateAcceleration(MassiveBody_t* body) 
{
    body->acceleration.x = body->netForce.x / body->mass;
    body->acceleration.y = body->netForce.y / body->mass;
}

void massiveBodyUpdateVelocity(MassiveBody_t* body)
{
    body->velocity.x += body->acceleration.x * deltaTime;
    body->velocity.y += body->acceleration.y * deltaTime;
}

void massiveBodyUpdate(MassiveBody_t* body)
{
    massiveBodyClearNetForce(body);
    massiveBodyUpdateAcceleration(body);
    massiveBodyUpdateVelocity(body);
    massiveBodyClearNetForce(body);
}

void massiveBodyStopMotion(MassiveBody_t* body)
{
    body->acceleration.x = FIXED_ZERO;
    body->acceleration.y = FIXED_ZERO;
    body->velocity.x = FIXED_ZERO;
    body->velocity.y = FIXED_ZERO;
    body->netForce.x = FIXED_ZERO;
    body->netForce.y = FIXED_ZERO;
}

void dynamicBodyUpdate(DynamicBody_t* body)
{
    massiveBodyUpdate(&body->massBody);
    body->transform.x += body->massBody.velocity.x * deltaTime;
    body->transform.y += body->massBody.velocity.y * deltaTime;
}


/**
 * Checks for collision between two square colliders using fixed-point math.
 * @return The side of collision FROM THE PERSPECTIVE OF OBJECT A.
 */
CollisionSide_t dynamicOnStaticBodyCollisionCheck(const DynamicBody_t* dynamicBody, const StaticBody_t* staticBody)
{
    // Calculate distance and combined radii using fixed-point operations
    Fixed_t dx = FIXED_SUB(dynamicBody->transform.x, staticBody->transform.x);
    Fixed_t dy = FIXED_SUB(dynamicBody->transform.y, staticBody->transform.y);
    Fixed_t combinedHalfWidths = FIXED_ADD(dynamicBody->collider.x, staticBody->collider.x);
    Fixed_t combinedHalfHeights = FIXED_ADD(dynamicBody->collider.y, staticBody->collider.y);

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
void dynamicOnStaticBodyResolveCollision(DynamicBody_t* dynamicBody, const StaticBody_t* staticBody, CollisionSide_t side)
{
    if (side == COLLISION_NONE) {
        return;
    }

    Vector2D_t* dynamicTransform = &dynamicBody->transform;
    const Vector2D_t*  dynamicCollider  = &dynamicBody->collider;
    const Vector2D_t* staticTransform = &staticBody->transform;
    const Vector2D_t*  staticCollider  = &staticBody->collider;
    Fixed_t combinedHalfWidths;
    Fixed_t combinedHalfHeights;
    
    switch (side) {
        case COLLISION_TOP:
            combinedHalfHeights = FIXED_ADD(dynamicCollider->y, staticCollider->y);
            dynamicTransform->y = FIXED_ADD(staticTransform->y, combinedHalfHeights);
            break;
        case COLLISION_BOTTOM:
            combinedHalfHeights = FIXED_ADD(dynamicCollider->y, staticCollider->y);
            dynamicTransform->y = FIXED_SUB(staticTransform->y, combinedHalfHeights);
            break;
        case COLLISION_RIGHT:
            combinedHalfWidths = FIXED_ADD(dynamicCollider->x, staticCollider->x);
            dynamicTransform->x = FIXED_SUB(staticTransform->x, combinedHalfWidths);
            break;
        case COLLISION_LEFT:
            combinedHalfWidths = FIXED_ADD(dynamicCollider->x, staticCollider->x);
            dynamicTransform->x = FIXED_ADD(staticTransform->x, combinedHalfWidths);
            break;
        case COLLISION_NONE:
            break;
    }
}