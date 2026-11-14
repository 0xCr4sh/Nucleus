/**
 * @file glfwPlatform.cpp
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

#include "glfwPlatform.h"
#include <GLFW/glfw3.h>
#include <core/logging/LogInternal.h>
#include "glfwWindow.h"
#include "nucleus/core/log.h"

#ifdef _WIN32
    #include <windows.h>
#elif __APPLE__
    #include <mach-o/dyld.h>
#else
    #include <unistd.h>
    #include <limits.h>
#endif

namespace nucleus {
    GlfwPlatform::GlfwPlatform() {
        if (!glfwInit())
        {
            NUC_CORE_CRITICAL("Failed to initialize GLFW.");
            return;
        }
    }

    GlfwPlatform::~GlfwPlatform() {
        glfwTerminate();
    }

    std::unique_ptr<IWindow> GlfwPlatform::CreateWindow(WindowSpecification specification) {
        return std::make_unique<GlfwWindow>(std::move(specification));
    }

    std::filesystem::path GlfwPlatform::GetExecutablePath() {
#ifdef _WIN32

        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        return std::filesystem::path(buffer);

#elif __APPLE__

        uint32_t size = 0;
        _NSGetExecutablePath(NULL, &size);

        std::string buffer(size, '\0');

        if (_NSGetExecutablePath(buffer.data(), &size) == 0)
            return std::filesystem::path(buffer.c_str());

        return "";

#else

        char buffer[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", buffer, PATH_MAX);

        if (count != -1) {
            return std::filesystem::path(std::string(buffer, count));
        }

        return "";

#endif
    }


    void GlfwPlatform::PollEvents() {
        glfwPollEvents();
    }
} // nucleus