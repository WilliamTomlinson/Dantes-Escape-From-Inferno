/** @file   fixed_vector_2d.h
    @author W. R. J. Tomlinson
    @date   14 Oct 2025
    @brief  General purpose 2D vector type and opperations.
*/

#ifndef FIXED_VECTOR_2D_H
#define FIXED_VECTOR_2D_H

#include <system.h>
#include "fixed_math.h"

/* Vector type structure.  */
typedef struct {
    Fixed_t x;
    Fixed_t y;
} FixedVector2D_t;

/** Initialises a vector with specified values.
    @param vector pointer to a vector to initialise
    @param x component of vector in x direction
    @param y component of vector in y direction  */
void fixedVectorInit(FixedVector2D_t* vector, Fixed_t x, Fixed_t y);

/** Returns the dot product of 2 vectors.
    @param vector1 a pointer to the first vector
    @param vector2 a pointer to the second vector
    @return the calculated dot product  */
Fixed_t fixedDotProduct(const FixedVector2D_t* vector1, const FixedVector2D_t* vector2);

/** Adds the elements of one vector to the coresponding
    elements of another vector.
    @param vector1 the vector where its elements are being added to
    @param vector2 the vector where its elements are used for adding  */
void fixedVectorAdd(FixedVector2D_t* vector1, const FixedVector2D_t* vector2);

/** Adds the elements of 2 vectors and returns a new one.
    @param vector1 pointer to the first vector
    @param vector2 pointer to the second vector  */
FixedVector2D_t fixedVectorSum(const FixedVector2D_t* vector1, const FixedVector2D_t* vector2);

/** Subtracts the elements of one vector from the coresponding elements of another vector.
    @param vector1 a pointer to the vector where its elements are being subtracted from
    @param vector2 a pointer to the vector where its elements are used for subtracting  */
void fixedVectorSub(FixedVector2D_t* vector1, const FixedVector2D_t* vector2);

/** Subtracts the elements of of two vectors and returns a new vector
    @param vector1 pointer to the vector being subtracted from
    @param vector2 pointer to the vector used for subtraction  */
FixedVector2D_t fixedVectorDifference(const FixedVector2D_t* vector1, const FixedVector2D_t* vector2);

/** Scales the elements of a vector by a constant.
    @param vector a pointer to the vector being scaled
    @param scalar the scaling factor for the vectors elements  */
void fixedVectorScale(FixedVector2D_t* vector, const Fixed_t scalar);

/** Returns a new vector type that is the same elements as the vector it is passed.
    @param vector a pointer to the vector that is being coppied  */
FixedVector2D_t fixedVectorCopy(const FixedVector2D_t* vector);

/** Returns the squared magnitude of a vector
    by performing the dot product on itself.
    @param vector the vector that is having its magnitude squared  */
Fixed_t fixedMagnitudeSquared(const FixedVector2D_t* vector);

#endif /* FIXED_VECTOR_2D_H */