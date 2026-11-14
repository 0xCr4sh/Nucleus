/**
 * @file LogInternal.h
 * @brief Internal logging interface for the Nucleus Engine.
 *
 * @details
 * Declares the internal logging interface used by the Nucleus Engine.
 *
 * Messages are formatted in this header using the C++20 formatting
 * library (std::format) and forwarded as finished strings to the
 * engine's core logger. The underlying logging library is not
 * included or exposed here; it is used only inside the
 * implementation file.
 *
 * Client applications write messages through the public logging
 * interface (log.h), which forwards to a separate client logger.
 *
 * This header is private to the engine implementation and
 * should not be included by client applications.
 *
 * The logging infrastructure must be initialized with
 * LogInternal::Init() before any message is written.
 *
 * @author Ridham
 * @date 2026-11-09
 *
 * @bug No known bugs.
 *
 * @copyright (c) 2026 Ridham
 */

#ifndef NUCLEUS_INTERNAL_LOG_H
#define NUCLEUS_INTERNAL_LOG_H

#include <format>
#include <string_view>
#include <utility>

namespace nucleus {

    /**
     * @class LogInternal
     * @brief Manages the engine's internal logging infrastructure.
     *
     * @details
     * Responsible for initializing and shutting down the logging
     * infrastructure, and for writing messages to the engine's
     * core logger at different severity levels.
     *
     * Supported severity levels:
     *
     * - Trace: Detailed diagnostic information.
     * - Debug: Information useful during development.
     * - Info: General engine information.
     * - Warn: Potential issues that do not prevent execution.
     * - Error: Errors that affect an operation.
     * - Critical: Severe errors that may prevent normal execution.
     *
     * The logging functions take a compile-time checked format
     * string. Formatting happens in the calling translation unit and
     * only the resulting std::string_view crosses into the
     * implementation, so no third-party logging types appear in
     * this header.
     *
     * This class is an implementation detail and is not
     * intended for use by client applications.
     *
     * This class is not intended to be instantiated.
     */
    class LogInternal {
    public:

        /**
         * @brief Initializes the logging infrastructure.
         *
         * @details
         * Configures the global logging pattern and creates
         * the core and client loggers.
         *
         * Both loggers are configured to accept trace-level
         * messages and above.
         *
         * Must be called before any logging function is used.
         */
        static void Init();

        /**
         * @brief Shuts down the logging infrastructure.
         *
         * @details
         * Releases the loggers and the registered logging
         * infrastructure managed by the underlying logging library.
         *
         * Should be called during engine shutdown. No logging
         * function may be used afterwards.
         */
        static void Shutdown();

        /**
         * @brief Logs a trace-level engine message.
         *
         * @tparam Args Types of the formatting arguments.
         * @param fmt Compile-time checked format string.
         * @param args Arguments used to construct the message.
         *
         * @details
         * Trace messages provide highly detailed information
         * useful when investigating engine behavior.
         */
        template<typename... Args>
        static void CoreTrace(std::format_string<Args...> fmt, Args&&... args) {
            CoreTraceImpl(std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Logs a debug-level engine message.
         *
         * @tparam Args Types of the formatting arguments.
         * @param fmt Compile-time checked format string.
         * @param args Arguments used to construct the message.
         *
         * @details
         * Debug messages provide information useful during
         * engine development and debugging.
         */
        template<typename... Args>
        static void CoreDebug(std::format_string<Args...> fmt, Args&&... args) {
            CoreDebugImpl(std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Logs an informational engine message.
         *
         * @tparam Args Types of the formatting arguments.
         * @param fmt Compile-time checked format string.
         * @param args Arguments used to construct the message.
         *
         * @details
         * Informational messages describe normal engine
         * activity and significant execution events.
         */
        template<typename... Args>
        static void CoreInfo(std::format_string<Args...> fmt, Args&&... args) {
            CoreInfoImpl(std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Logs an engine warning.
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
        static void CoreWarn(std::format_string<Args...> fmt, Args&&... args) {
            CoreWarnImpl(std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Logs an engine error.
         *
         * @tparam Args Types of the formatting arguments.
         * @param fmt Compile-time checked format string.
         * @param args Arguments used to construct the message.
         *
         * @details
         * Error messages indicate failures in an operation
         * or unexpected engine behavior.
         */
        template<typename... Args>
        static void CoreError(std::format_string<Args...> fmt, Args&&... args) {
            CoreErrorImpl(std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Logs a critical engine error.
         *
         * @tparam Args Types of the formatting arguments.
         * @param fmt Compile-time checked format string.
         * @param args Arguments used to construct the message.
         *
         * @details
         * Critical messages indicate severe failures that may
         * prevent the engine from continuing normally.
         */
        template<typename... Args>
        static void CoreCritical(std::format_string<Args...> fmt, Args&&... args) {
            CoreCriticalImpl(std::format(fmt, std::forward<Args>(args)...));
        }

    private:

        /** @brief Forwards a trace message to the core logger. */
        static void CoreTraceImpl(std::string_view message);

        /** @brief Forwards a debug message to the core logger. */
        static void CoreDebugImpl(std::string_view message);

        /** @brief Forwards an informational message to the core logger. */
        static void CoreInfoImpl(std::string_view message);

        /** @brief Forwards a warning message to the core logger. */
        static void CoreWarnImpl(std::string_view message);

        /** @brief Forwards an error message to the core logger. */
        static void CoreErrorImpl(std::string_view message);

        /** @brief Forwards a critical message to the core logger. */
        static void CoreCriticalImpl(std::string_view message);
    };

}


/**
 * @name Nucleus Core Logging Macros
 * @brief Convenience macros for internal engine logging.
 *
 * @details
 * These macros forward their arguments to the corresponding
 * LogInternal logging function.
 *
 * They are intended exclusively for use within the engine
 * implementation.
 *
 * Example:
 *
 * @code
 * NUC_CORE_INFO("Engine initialized.");
 * NUC_CORE_WARN("Window resize event received: {}x{}", width, height);
 * NUC_CORE_ERR("Failed to initialize renderer: {}", reason);
 * @endcode
 *
 * @{
 */

/** @brief Logs an informational engine message. */
#define NUC_CORE_INFO(...)       ::nucleus::LogInternal::CoreInfo(__VA_ARGS__)

/** @brief Logs an engine warning. */
#define NUC_CORE_WARN(...)       ::nucleus::LogInternal::CoreWarn(__VA_ARGS__)

/** @brief Logs an engine error. */
#define NUC_CORE_ERR(...)        ::nucleus::LogInternal::CoreError(__VA_ARGS__)

/** @brief Logs a critical engine error. */
#define NUC_CORE_CRITICAL(...)   ::nucleus::LogInternal::CoreCritical(__VA_ARGS__)

#if defined(NUCLEUS_RELEASE)
#define NUC_CORE_TRACE(...)  ((void)0)
#define NUC_CORE_DEBUG(...)  ((void)0)
#else

/** @brief Logs a trace-level engine message. */
#define NUC_CORE_TRACE(...)      ::nucleus::LogInternal::CoreTrace(__VA_ARGS__)

/** @brief Logs a debug-level engine message. */
#define NUC_CORE_DEBUG(...)      ::nucleus::LogInternal::CoreDebug(__VA_ARGS__)

#endif

/** @} */

#endif // NUCLEUS_INTERNAL_LOG_H