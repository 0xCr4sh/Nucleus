/**
* @file numericalAliases.h
 * @brief Defines fixed-width numerical type aliases used throughout Nucleus.
 *
 * @details
 * Provides convenient, consistent aliases for commonly used numerical types,
 * including signed integers, unsigned integers, and floating-point values.
 *
 * Integer aliases use the fixed-width types provided by the C++ standard
 * library, ensuring their bit widths remain consistent across supported
 * platforms and architectures.
 *
 * These aliases serve as foundational types for the Nucleus Engine and are
 * intended to be used across its core systems and subsystems.
 *
 * @author Ridham
 * @date 2026-11-10
 *
 * @bug No known bugs.
 *
 * @copyright (c) 2026 Ridham
 */

#ifndef NUCLEUS_NUMERICAL_ALIASES_H
#define NUCLEUS_NUMERICAL_ALIASES_H

#include <cstdint>

namespace nucleus
{
    /**
     * @brief 32-bit floating-point type.
     */
    using f32 = float;

    /**
     * @brief 64-bit floating-point type.
     */
    using f64 = double;

    /**
     * @brief 8-bit signed integer type.
     */
    using i8  = int8_t;

    /**
     * @brief 8-bit unsigned integer type.
     */
    using u8  = uint8_t;

    /**
     * @brief 16-bit signed integer type.
     */
    using i16 = int16_t;

    /**
     * @brief 16-bit unsigned integer type.
     */
    using u16 = uint16_t;

    /**
     * @brief 32-bit signed integer type.
     */
    using i32 = int32_t;

    /**
     * @brief 32-bit unsigned integer type.
     */
    using u32 = uint32_t;

    /**
     * @brief 64-bit signed integer type.
     */
    using i64 = int64_t;

    /**
     * @brief 64-bit unsigned integer type.
     */
    using u64 = uint64_t;
}

#endif