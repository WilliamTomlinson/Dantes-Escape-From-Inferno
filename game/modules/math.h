/** @file   math.h
    @author W. R. J. Tomlinson
    @date   14 Oct 2025
    @brief  A math module that implements fixed_point numbers and 2D vectors.
*/


#ifndef MATH_H
#define MATH_H

#include "system.h"

//==================================================================
// 1. CORE DEFINITIONS
//==================================================================

// Our fixed-point type: Q9.6 format
// Range: -512.0 to +511.984
// Precision: 1/64 = 0.0156
typedef int16_t Fixed_t;

// The number of fractional bits
#define FRAC_BITS 6


//==================================================================
// 2. CONVERSION MACROS
//==================================================================

// Convert an integer to fixed-point
#define INT_TO_FIXED(x)    ((Fixed_t)((x) << FRAC_BITS))

// Convert a fixed-point to the nearest integer (rounding)
// Adding half the fractional part before shifting effectively rounds the number.
#define FIXED_TO_INT(x)    (((x) + (1 << (FRAC_BITS - 1))) >> FRAC_BITS)

// Convert a fixed-point to a truncated integer (faster, less accurate)
#define FIXED_TO_INT_TRUNC(x) ((x) >> FRAC_BITS)

// Convert a float to fixed-point (for initial values, not for runtime)
#define FLOAT_TO_FIXED(x)  ((Fixed_t)((x) * (1 << FRAC_BITS)))


//==================================================================
// 3. ARITHMETIC OPERATORS
//==================================================================

// ADDITION: Simple integer addition. Fast and efficient.
#define FIXED_ADD(a, b)    ((Fixed_t)((a) + (b)))

// SUBTRACTION: Simple integer subtraction. Fast and efficient.
#define FIXED_SUB(a, b)    ((Fixed_t)((a) - (b)))

// MULTIPLICATION:
// Must use a 32-bit intermediate to prevent overflow, then scale back.
// (a * b) results in a Q16.16 number, so we shift right by FRAC_BITS.
#define FIXED_MUL(a, b)    ((Fixed_t)((((int32_t)(a)) * ((int32_t)(b))) >> FRAC_BITS))

// DIVISION:
// Must scale the numerator UP before dividing to preserve precision.
// (a << FRAC_BITS) / b results in a Q8.8 number.
#define FIXED_DIV(a, b)    ((Fixed_t)((((int32_t)(a)) << FRAC_BITS) / (b)))


//==================================================================
// 4. UTILITY AND COMPARISON
//==================================================================

// ABSOLUTE VALUE
#define FIXED_ABS(x)       ((x) < 0 ? -(x) : (x))

// COMPARISON: Standard integer comparison works perfectly.
#define FIXED_LT(a, b)     ((a) < (b))
#define FIXED_GT(a, b)     ((a) > (b))
#define FIXED_LTE(a, b)    ((a) <= (b))
#define FIXED_GTE(a, b)    ((a) >= (b))
#define FIXED_EQ(a, b)     ((a) == (b))


//==================================================================
// 5. USEFUL CONSTANTS
//==================================================================

#define FIXED_ONE          INT_TO_FIXED(1)      // Represents 1.0 (value = 256)
#define FIXED_HALF         INT_TO_FIXED(1) >> 1 // Represents 0.5 (value = 128)
#define FIXED_ZERO         INT_TO_FIXED(0)      // Represents 0.0 (value = 0)
#define FIXED_PI           FLOAT_TO_FIXED(3.14159f) // Represents PI (value = 804)


//==================================================================
// 6. VECTORS
//==================================================================



typedef struct {
    Fixed_t x;
    Fixed_t y;
} Vector2D_t;


/** Returns the dot product of 2 vectors.
    @param vector1 a pointer to the first vector
    @param vector2 a pointer to the second vector
    @return the calculated dot product  */
Fixed_t dotProduct(const Vector2D_t* vector1, const Vector2D_t* vector2);


/** Adds the elements of 2 vectors and returns a new one.
    @param vector1 pointer to the first vector
    @param vector2 pointer to the second vector  */
Vector2D_t vectorSum(const Vector2D_t* vector1, const Vector2D_t* vector2);


/** Subtracts the elements of of two vectors and returns a new vector
    @param vector1 pointer to the vector being subtracted from
    @param vector2 pointer to the vector used for subtraction  */
Vector2D_t vectorSub(const Vector2D_t* vector1, const Vector2D_t* vector2);


/** Returns a scaled vector
    @param vector a pointer to the vector being scaled
    @param scalar the scaling factor for the vectors elements  */
Vector2D_t fixedVectorScale(Vector2D_t* vector, const Fixed_t scalar);


/** Returns a copy of the passed vector
    @param vector a pointer to the vector that is being coppied  */
Vector2D_t fixedVectorCopy(const Vector2D_t* vector);


/** Returns the squared magnitude of a vector.
    @param vector the vector that is having its magnitude squared  */
Fixed_t fixedMagnitudeSquared(const Vector2D_t* vector);


#endif /* MATH_H */