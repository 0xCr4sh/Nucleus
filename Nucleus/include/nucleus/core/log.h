
/**
 * @file log.h
 * @brief Public logging interface for Nucleus applications.
 *
 * @details
 * Provides a centralized logging interface for applications
 * built using the Nucleus Engine.
 *
 * The Log class exposes multiple logging severity levels,
 * allowing client applications to report messages through
 * the Nucleus logging infrastructure.
 *
 * Internally, messages are formatted using the C++20 formatting
 * library and forwarded to the client's application logger.
 *
 * The underlying logging implementation is hidden from clients.
 * Applications do not need to depend directly on the logging
 * library used internally by Nucleus.
 *
 * Logging must be initialized by the engine before the
 * application attempts to write log messages.
 *
 * @author Ridham
 * @date 2026-11-09
 *
 * @bug No known bugs.
 *
 * @copyright (c) 2026 Ridham
 */

#ifndef NUCLEUS_LOG_H
#define NUCLEUS_LOG_H

#include "../export.h"

#include <format>
#include <string_view>
#include <utility>

namespace nucleus {

    /**
     * @class log
     * @brief Provides logging functionality to client applications.
     *
     * @details
     * The Log class provides a static interface for writing
     * application messages at different severity levels.
     *
     * Supported severity levels:
     *
     * - Trace: Detailed diagnostic information.
     * - Debug: Information useful during development.
     * - Info: General application information.
     * - Warn: Potential issues that do not prevent execution.
     * - Error: Errors that affect an operation.
     * - Critical: Severe errors that may prevent normal execution.
     *
     * Messages support C++20 compile-time checked formatting.
     *
     * The implementation is intentionally separated from the
     * underlying logging library to avoid exposing implementation
     * details through the public API.
     *
     * This class is not intended to be instantiated.
     */
    class NUCLEUS_API log {
    public:

        /**
         * @brief Logs a trace-level message.
         *
         * @tparam Args Types of the formatting arguments.
         * @param fmt Compile-time checked format string.
         * @param args Arguments used to construct the message.
         *
         * @details
         * Trace messages provide highly detailed information
         * useful when investigating application behavior.
         */
        template<typename... Args>
        static void trace(
            std::format_string<Args...> fmt,
            Args&&... args
        ) {
            trace_impl(
                std::format(fmt, std::forward<Args>(args)...)
            );
        }

        /**
         * @brief Logs a debug-level message.
         *
         * @tparam Args Types of the formatting arguments.
         * @param fmt Compile-time checked format string.
         * @param args Arguments used to construct the message.
         *
         * @details
         * Debug messages provide information useful during
         * application development and debugging.
         */
        template<typename... Args>
        static void debug(
            std::format_string<Args...> fmt,
            Args&&... args
        ) {
            debug_impl(
                std::format(fmt, std::forward<Args>(args)...)
            );
        }

        /**
         * @brief Logs an informational message.
         *
         * @tparam Args Types of the formatting arguments.
         * @param fmt Compile-time checked format string.
         * @param args Arguments used to construct the message.
         *
         * @details
         * Informational messages describe normal application
         * activity and significant execution events.
         */
        template<typename... Args>
        static void info(
            std::format_string<Args...> fmt,
            Args&&... args
        ) {
            info_impl(
                std::format(fmt, std::forward<Args>(args)...)
            );
        }

        /**
         * @brief Logs a warning message.
         *
         * @tparam Args Types of the formatting arguments.
         * @param fmt Compile-time checked format string.
         * @param args Arguments used to construct the message.
         *
         * @details
         * Warning messages indicate potentially problematic
         * situations that do not necessarily prevent execution.
         */
        template<typename... Args>
        static void warn(
            std::format_string<Args...> fmt,
            Args&&... args
        ) {
            warn_impl(
                std::format(fmt, std::forward<Args>(args)...)
            );
        }

        /**
         * @brief Logs an error message.
         *
         * @tparam Args Types of the formatting arguments.
         * @param fmt Compile-time checked format string.
         * @param args Arguments used to construct the message.
         *
         * @details
         * Error messages indicate failures in an operation
         * or unexpected application behavior.
         */
        template<typename... Args>
        static void error(
            std::format_string<Args...> fmt,
            Args&&... args
        ) {
            error_impl(
                std::format(fmt, std::forward<Args>(args)...)
            );
        }

        /**
         * @brief Logs a critical error message.
         *
         * @tparam Args Types of the formatting arguments.
         * @param fmt Compile-time checked format string.
         * @param args Arguments used to construct the message.
         *
         * @details
         * Critical messages indicate severe failures that may
         * prevent the application from continuing normally.
         */
        template<typename... Args>
        static void critical(
            std::format_string<Args...> fmt,
            Args&&... args
        ) {
            critical_impl(
                std::format(fmt, std::forward<Args>(args)...)
            );
        }

    private:

        /** @brief Forwards a trace message to the client logger. */
        static void trace_impl(std::string_view message);

        /** @brief Forwards a debug message to the client logger. */
        static void debug_impl(std::string_view message);

        /** @brief Forwards an informational message to the client logger. */
        static void info_impl(std::string_view message);

        /** @brief Forwards a warning message to the client logger. */
        static void warn_impl(std::string_view message);

        /** @brief Forwards an error message to the client logger. */
        static void error_impl(std::string_view message);

        /** @brief Forwards a critical message to the client logger. */
        static void critical_impl(std::string_view message);
    };

}


/**
 * @name Application Logging Macros
 * @brief Convenience macros for application logging.
 *
 * @details
 * These macros provide a shorter interface to the Nucleus Log
 * class and forward their arguments to the corresponding
 * logging function.
 *
 * They are intended exclusively for applications using Nucleus.
 *
 * Example:
 *
 * @code
 * NUC_INFO("Application started.");
 * NUC_WARN("Unexpected value: {}", value);
 * NUC_ERR("Failed to load resource: {}", resourcePath);
 * @endcode
 *
 * @{
 */

/** @brief Logs an informational application message. */
#define NUC_INFO(...)       ::nucleus::log::info(__VA_ARGS__)

/** @brief Logs an application warning. */
#define NUC_WARN(...)       ::nucleus::log::warn(__VA_ARGS__)

/** @brief Logs an application error. */
#define NUC_ERR(...)        ::nucleus::log::error(__VA_ARGS__)

/** @brief Logs a critical application error. */
#define NUC_CRITICAL(...)   ::nucleus::log::critical(__VA_ARGS__)


#if defined(NUCLEUS_RELEASE)
#define NUC_TRACE(...)  ((void)0)
#define NUC_DEBUG(...)  ((void)0)
#else

/** @brief Logs a trace-level application message. */
#define NUC_TRACE(...)      ::nucleus::log::trace(__VA_ARGS__)

/** @brief Logs a debug-level application message. */
#define NUC_DEBUG(...)      ::nucleus::log::debug(__VA_ARGS__)

#endif


/** @} */

#endif // NUCLEUS_LOG_H
