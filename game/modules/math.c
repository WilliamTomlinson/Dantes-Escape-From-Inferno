/** @file   math.c
    @author W. R. J. Tomlinson
    @date   21 Oct 2025
    @brief  A math module that implements fixed_point numbers and 2D vectors.
*/

#include "math.h"

/** Returns the dot product of 2 vectors.
    @param vector1 a pointer to the first vector
    @param vector2 a pointer to the second vector
    @return the calculated dot product  */
Fixed_t dotProduct(const Vector2D_t* vector1, const Vector2D_t* vector2)
{
    Fixed_t xProduct = FIXED_MUL(vector1->x, vector2->x);
    Fixed_t yProduct = FIXED_MUL(vector1->y, vector2->y);
    return FIXED_ADD(xProduct, yProduct);
}


/** Adds the elements of 2 vectors and returns a new one.
    @param vector1 pointer to the first vector
    @param vector2 pointer to the second vector  */
Vector2D_t vectorSum(const Vector2D_t* vector1, const Vector2D_t* vector2)
{
    Vector2D_t newVector;
    newVector.x = FIXED_ADD(vector1->x, vector2->x);
    newVector.y = FIXED_ADD(vector1->y, vector2->y);
    return newVector;
}


/** Subtracts the elements of of two vectors and returns a new vector
    @param vector1 pointer to the vector being subtracted from
    @param vector2 pointer to the vector used for subtraction  */
Vector2D_t vectorSub(const Vector2D_t* vector1, const Vector2D_t* vector2)
{
    Vector2D_t newVector;
    newVector.x = FIXED_SUB(vector1->x, vector2->x);
    newVector.y = FIXED_SUB(vector1->y, vector2->y);
    return newVector;
}


/** Returns a scaled vector
    @param vector a pointer to the vector being scaled
    @param scalar the scaling factor for the vectors elements  */
Vector2D_t vectorScale(const Vector2D_t* vector, Fixed_t scalar)
{
    Vector2D_t newVector;
    newVector.x = FIXED_MUL(vector->x, scalar);
    newVector.y = FIXED_MUL(vector->y, scalar);
    return newVector;
}

/** Returns a copy of the passed vector
    @param vector a pointer to the vector that is being coppied  */
Vector2D_t vectorCopy(const Vector2D_t* vector)
{
    return *vector;
}


/** Returns the squared magnitude of a vector.
    @param vector the vector that is having its magnitude squared  */
Fixed_t magnitudeSquared(const Vector2D_t* vector)
{
    Fixed_t xSquared = FIXED_MUL(vector->x, vector->x);
    Fixed_t ySquared = FIXED_MUL(vector->y, vector->y);
    return FIXED_ADD(xSquared, ySquared);
}
