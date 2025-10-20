/** @file   fixed_vector_2d.c
    @author W. R. J. Tomlinson
    @date   14 Oct 2025
    @brief  General purpose 2D vector type and opperations.
*/

#include "fixed_vector_2d.h"

/** Initialises a vector with specified values.
    @param vector pointer to a vector to initialise
    @param x component of vector in x direction
    @param y component of vector in y direction  */
void fixedVectorInit(FixedVector2D_t* vector, Fixed_t x, Fixed_t y)
{
    vector->x = x;
    vector->y = y;
}

/** Returns the dot product of 2 vectors.
    @param vector1 a pointer to the first vector
    @param vector2 a pointer to the second vector
    @return the calculated dot product  */
Fixed_t fixedDotProduct(const FixedVector2D_t* vector1, const FixedVector2D_t* vector2)
{
    Fixed_t xProduct = FIXED_MUL(vector1->x, vector2->x);
    Fixed_t yProduct = FIXED_MUL(vector1->y, vector2->y);
    return FIXED_ADD(xProduct, yProduct);
}

/** Adds the elements of one vector to the coresponding
    elements of another vector.
    @param vector1 the vector where its elements are being added to
    @param vector2 the vector where its elements are used for adding  */
void fixedVectorAdd(FixedVector2D_t* vector1, const FixedVector2D_t* vector2)
{
    vector1->x = FIXED_ADD(vector1->x, vector2->x);
    vector1->y = FIXED_ADD(vector1->y, vector2->y);
}

/** Adds the elements of 2 vectors and returns a new one.
    @param vector1 pointer to the first vector
    @param vector2 pointer to the second vector  */
FixedVector2D_t fixedVectorSum(const FixedVector2D_t* vector1, const FixedVector2D_t* vector2)
{
    FixedVector2D_t newVector;
    newVector.x = FIXED_ADD(vector1->x, vector2->x);
    newVector.y = FIXED_ADD(vector1->y, vector2->y);
    return newVector;
}

/** Subtracts the elements of one vector from the coresponding elements of another vector.
    @param vector1 a pointer to the vector where its elements are being subtracted from
    @param vector2 a pointer to the vector where its elements are used for subtracting  */
void fixedVectorSub(FixedVector2D_t* vector1, const FixedVector2D_t* vector2)
{
    vector1->x = FIXED_SUB(vector1->x, vector2->x);
    vector1->y = FIXED_SUB(vector1->y, vector2->y);
}

/** Returns a new vector that is the difference of two vectors. */
FixedVector2D_t fixedVectorDifference(const FixedVector2D_t* vector1, const FixedVector2D_t* vector2)
{
    FixedVector2D_t newVector;
    newVector.x = FIXED_SUB(vector1->x, vector2->x);
    newVector.y = FIXED_SUB(vector1->y, vector2->y);
    return newVector;
}

/** Scales the elements of a vector by a constant.
    @param vector a pointer to the vector being scaled
    @param scalar the scaling factor for the vectors elements  */
void fixedVectorScale(FixedVector2D_t* vector, Fixed_t scalar)
{
    vector->x = FIXED_MUL(vector->x, scalar);
    vector->y = FIXED_MUL(vector->y, scalar);
}

/** Scales the elements of a vector by a constant.
    @param vector a pointer to the vector being scaled
    @param scalar the scaling factor for the vectors elements  */
FixedVector2D_t fixedVectorScaled(const FixedVector2D_t* vector, Fixed_t scalar)
{
    FixedVector2D_t newVector;
    newVector.x = FIXED_MUL(vector->x, scalar);
    newVector.y = FIXED_MUL(vector->y, scalar);
    return newVector;
}

/** Returns a new vector type that is the same elements as the vector it is passed.
    @param vector a pointer to the vector that is being coppied  */
FixedVector2D_t fixedVectorCopy(const FixedVector2D_t* vector)
{
    return *vector;
}


/** Returns the squared magnitude of a vector
    by performing the dot product on itself.
    @param vector the vector that is having its magnitude squared  */
Fixed_t fixedMagnitudeSquared(const FixedVector2D_t* vector)
{
    Fixed_t xSquared = FIXED_MUL(vector->x, vector->x);
    Fixed_t ySquared = FIXED_MUL(vector->y, vector->y);
    return FIXED_ADD(xSquared, ySquared);
}
