
/**
 * @file log.cpp
 * @brief Implements the Nucleus logging infrastructure.
 *
 * @details
 * Contains the implementation of the internal logging system
 * and the public application logging interface.
 *
 * Uses spdlog as the underlying logging library and maintains
 * two independent color-enabled console loggers:
 *
 * - NUCLEUS: Used for internal engine messages.
 * - APP: Used for client application messages.
 *
 * The public Log interface forwards application messages
 * to the client logger without exposing spdlog to clients.
 *
 * Both loggers use a shared output pattern displaying the
 * timestamp, logger name, and message.
 *
 * @author Ridham
 * @date 2026-11-09
 *
 * @bug No known bugs.
 *
 * @copyright (c) 2026 Ridham
 */

#include "LogInternal.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <nucleus/core/log.h>

namespace nucleus {

    static std::shared_ptr<spdlog::logger> CoreLogger;

    static std::shared_ptr<spdlog::logger> ClientLogger;



    void LogInternal::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        CoreLogger = spdlog::stdout_color_mt("NUCLEUS");
        CoreLogger->set_level(spdlog::level::trace);

        ClientLogger = spdlog::stdout_color_mt("APP");
        ClientLogger->set_level(spdlog::level::trace);
    }


    void LogInternal::Shutdown() {
        spdlog::shutdown();

        CoreLogger.reset();
        ClientLogger.reset();
    }


    // -------------------------------------------------------------------------
    // Public application logging implementation
    // -------------------------------------------------------------------------

    void log::trace_impl(std::string_view message) {
        ClientLogger->trace("{}", message);
    }


    void log::debug_impl(std::string_view message) {
        ClientLogger->debug("{}", message);
    }


    void log::info_impl(std::string_view message) {
        ClientLogger->info("{}", message);
    }



    void log::warn_impl(std::string_view message) {
        ClientLogger->warn("{}", message);
    }



    void log::error_impl(std::string_view message) {
        ClientLogger->error("{}", message);
    }



    void log::critical_impl(std::string_view message) {
        ClientLogger->critical("{}", message);
    }

    void LogInternal::CoreTraceImpl(std::string_view m) {
        CoreLogger->trace("{}", m);
    }

    void LogInternal::CoreDebugImpl(std::string_view m) {
        CoreLogger->debug("{}", m);
    }

    void LogInternal::CoreInfoImpl(std::string_view m) {
        CoreLogger->info("{}", m);
    }

    void LogInternal::CoreWarnImpl(std::string_view m) {
        CoreLogger->warn("{}", m);
    }

    void LogInternal::CoreErrorImpl(std::string_view m) {
        CoreLogger->error("{}", m);
    }

    void LogInternal::CoreCriticalImpl(std::string_view m) {
        CoreLogger->critical("{}", m);
    }
}
