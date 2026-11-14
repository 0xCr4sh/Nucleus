/**
 * @file glfwPlatform.h
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

#ifndef NUCLEUS_GLFWPLATFORM_H
#define NUCLEUS_GLFWPLATFORM_H

#include <platform/platform.h>

namespace nucleus {
    class GlfwPlatform final : public IPlatform {
    public:
        GlfwPlatform();
        ~GlfwPlatform() override;

        std::unique_ptr<IWindow> CreateWindow(
            WindowSpecification specification
        ) override;

        std::filesystem::path GetExecutablePath() override;

        void PollEvents() override;
    };
} // nucleus

#endif //NUCLEUS_GLFWPLATFORM_H
