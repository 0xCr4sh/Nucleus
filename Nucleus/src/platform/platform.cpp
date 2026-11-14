/**
 * @file platform.cpp
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

#include "platform.h"
#include "glfw/glfwPlatform.h"

namespace nucleus {
    std::unique_ptr<IPlatform> IPlatform::Create() {
        return std::make_unique<GlfwPlatform>();
    }
}
