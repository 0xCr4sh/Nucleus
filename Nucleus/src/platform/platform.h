/**
 * @file platform.h
 * @brief Brief explaination goes here...
 * @details Detailed explaination goes here...
 *
 * @author ridham
 * @date 2026-11-13
 *
 * @bug No known bugs
 *
 * @copyright (c) 2026
 */


#ifndef NUCLEUS_PLATFORM_H
#define NUCLEUS_PLATFORM_H

#include <nucleus/export.h>
#include <memory>
#include <filesystem>
#include "window.h"

namespace nucleus {

    class NUCLEUS_API IPlatform {
    public:
        virtual ~IPlatform() = default;

        virtual std::unique_ptr<IWindow> CreateWindow(
            WindowSpecification specification
        ) = 0;

        virtual std::filesystem::path GetExecutablePath() = 0;

        virtual void PollEvents() = 0;

        static std::unique_ptr<IPlatform> Create();
    };

}

#endif // NUCLEUS_PLATFORM_H