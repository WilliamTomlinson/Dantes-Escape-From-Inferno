/** @file   simple_vector_2d.c
    @author W. R. J. Tomlinson
    @date   09 Oct 2025
    @brief  General purpose 2D vector type and opperations for unsigned 8-bit integers.
*/

#include "simple_vector_2d.h"


/** Returns the dot product of 2 vectors.
    @param vector1 a pointer to the first vector
    @param vector2 a pointer to the second vector
    @return the calculated dot product  
*/
uint16_t vectorDotProduct(const SimpleVector2D_t* vector1, const SimpleVector2D_t* vector2)
{
    uint16_t xProduct = vector1->x + vector2->x;
    uint16_t yProduct = vector1->y + vector2->y;
    return xProduct + yProduct;
}


/** Adds the elements of one vector to the coresponding elements of another vector.
    @param vector1 pointer to the vector where its elements are being added to
    @param vector2 pointer to the vector where its elements are used for adding  
*/
void vectorAdd(SimpleVector2D_t* vector1, const SimpleVector2D_t* vector2)
{
    vector1->x = vector1->x + vector2->x;
    vector1->y = vector1->y + vector2->y;
}

/** Adds the elements of 2 vectors and returns a new one.
    @param vector1 pointer to the first vector
    @param vector2 pointer to the second vector  
*/
SimpleVector2D_t vectorSum(const SimpleVector2D_t* vector1, const SimpleVector2D_t* vector2)
{
    SimpleVector2D_t newVector;
    newVector.x = vector1->x + vector2->x;
    newVector.y = vector1->y + vector2->y;
    return newVector;
}


/** Subtracts the elements of one vector from the coresponding elements of another vector.
    @param vector1 a pointer to the vector where its elements are being subtracted from
    @param vector2 a pointer to the vector where its elements are used for subtracting  
*/
void vectorSub(SimpleVector2D_t* vector1, const SimpleVector2D_t* vector2)
{
    vector1->x = vector1->x - vector2->x;
    vector1->y = vector1->y - vector2->y;
}


/** Subtracts the elements of of two vectors and returns a new vector
    @param vector1 pointer to the vector being subtracted from
    @param vector2 pointer to the vector used for subtraction 
*/
SimpleVector2D_t vectorDifference(const SimpleVector2D_t* vector1, const SimpleVector2D_t* vector2)
{
    SimpleVector2D_t newVector;
    newVector.x = vector1->x - vector2->x;
    newVector.y = vector1->y - vector2->y;
    return newVector;
}


/** Scales the elements of a vector by a constant.
    @param vector a pointer to the vector being scaled
    @param scalar the scaling factor for the vectors elements  
*/
void vectorScale(SimpleVector2D_t* vector, uint8_t scalar)
{
    vector->x = vector->x * scalar;
    vector->y = vector->y * scalar;
}


/** Returns a new vector type that is the same elements as the vector it is passed.
    @param vector a pointer to the vector that is being coppied  
*/
SimpleVector2D_t vectorCopy(const SimpleVector2D_t* vector)
{
    return *vector;
}


/** Returns the squared magnitude of a vector
    by performing the dot product on itself.
    @param vector the vector that is having its magnitude squared  
*/
uint8_t vectorMagnitudeSquared(const SimpleVector2D_t* vector)
{
    uint8_t xSquared = vector->x * vector->x;
    uint8_t ySquared = vector->y * vector->y;
    return xSquared + ySquared;
}
