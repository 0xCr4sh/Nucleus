/**
 * @file glfwWindow.h
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

#ifndef NUCLEUS_GLFWWINDOW_H
#define NUCLEUS_GLFWWINDOW_H

#include <platform/window.h>
#include <GLFW/glfw3.h>

namespace nucleus {
    class GlfwWindow final : public IWindow {
    public:
        explicit GlfwWindow(WindowSpecification  specs);
        ~GlfwWindow() override;

        void SwapBuffers() override;

        [[nodiscard]] constexpr u64 GetWidth() const override;
        [[nodiscard]] constexpr u64 GetHeight() const override;

        void SetVsync(bool vsync) override;

        void Close() override;

        [[nodiscard]] void* GetNativeHandle() const override;

        void SetEventCallback(std::function<void(IEvent&)> callback) override;

    private:
        WindowSpecification m_WindowSpecifications;
        GLFWwindow* m_Window = nullptr;
        bool m_Opened = true;
        std::function<void(IEvent&)> m_EventCallback = nullptr;

        f64 m_MouseLastX = 0.0;
        f64 m_MouseLastY = 0.0;

    };
} // nucleus

#endif //NUCLEUS_GLFWWINDOW_H
