/** @file   fixed_math.h
    @author W. R. J. Tomlinson
    @date   14 Oct 2025
    @brief  Fixed-point math utilities using Q9.6 format (signed 16-bit).
            Provides arithmetic, conversion, and comparison macros with a
            numeric range of -512.0 to +511.984375 and a precision of 1/64.
*/

#ifndef FIXED_MATH_H
#define FIXED_MATH_H

#include <system.h>

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

#endif // FIXED_MATH_H