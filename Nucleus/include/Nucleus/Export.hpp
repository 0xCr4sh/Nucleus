
/**
 * @file Export.hpp
 * @brief Defines platform, compiler and shared library export macros.
 *
 * @details
 * This header provides a centralized collection of preprocessor macros
 * for identifying the target platform and compiler, as well as controlling
 * symbol visibility when building or consuming the Nucleus shared library.
 *
 * Platform detection:
 * - NUCLEUS_PLATFORM_WINDOWS
 * - NUCLEUS_PLATFORM_LINUX
 * - NUCLEUS_PLATFORM_MACOS
 * - NUCLEUS_PLATFORM_ANDROID
 * - NUCLEUS_PLATFORM_IOS
 *
 * Compiler detection:
 * - NUCLEUS_COMPILER_MSVC
 * - NUCLEUS_COMPILER_CLANG
 * - NUCLEUS_COMPILER_GCC
 *
 * Symbol visibility:
 * - NUCLEUS_API
 *
 * NUCLEUS_API automatically switches between exporting and importing
 * symbols on Windows. On platforms supporting GCC-style visibility
 * attributes, it marks symbols as externally visible.
 *
 * When compiling Nucleus itself, NUCLEUS_BUILD must be defined.
 *
 * @author Ridham
 * @date 2026-11-09
 *
 * @bug No known bugs.
 *
 * @copyright (c) 2026 Ridham
 */

#ifndef NUCLEUS_EXPORT_HPP
#define NUCLEUS_EXPORT_HPP


/* ============================================================
 * Platform Detection
 * ============================================================ */

#if defined(_WIN32) || defined(_WIN64)

    #define NUCLEUS_PLATFORM_WINDOWS

#elif defined(__ANDROID__)

    #define NUCLEUS_PLATFORM_ANDROID

#elif defined(__APPLE__)

    #include <TargetConditionals.h>

    #if TARGET_OS_IPHONE
        #define NUCLEUS_PLATFORM_IOS
    #else
        #define NUCLEUS_PLATFORM_MACOS
    #endif

#elif defined(__linux__)

    #define NUCLEUS_PLATFORM_LINUX

#endif


/* ============================================================
 * Compiler Detection
 * ============================================================ */

#if defined(_MSC_VER)

    #define NUCLEUS_COMPILER_MSVC

#elif defined(__clang__)

    #define NUCLEUS_COMPILER_CLANG

#elif defined(__GNUC__)

    #define NUCLEUS_COMPILER_GCC

#endif


/* ============================================================
 * Shared Library Symbol Visibility
 * ============================================================ */

#if defined(NUCLEUS_PLATFORM_WINDOWS)

    #if defined(NUCLEUS_BUILD)

        /**
         * @brief Exports a symbol from the Nucleus DLL.
         */
        #define NUCLEUS_API __declspec(dllexport)

    #else

        /**
         * @brief Imports a symbol from the Nucleus DLL.
         */
        #define NUCLEUS_API __declspec(dllimport)

    #endif

#elif defined(NUCLEUS_COMPILER_GCC) || \
      defined(NUCLEUS_COMPILER_CLANG)

    /**
     * @brief Marks a symbol as externally visible.
     */
    #define NUCLEUS_API __attribute__((visibility("default")))

#else

    /**
     * @brief Fallback when explicit symbol visibility is unavailable.
     */
    #define NUCLEUS_API

#endif


#endif // NUCLEUS_EXPORT_HPP