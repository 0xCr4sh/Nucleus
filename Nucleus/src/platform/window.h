/**
 * @file window.h
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


#ifndef NUCLEUS_WINDOW_H
#define NUCLEUS_WINDOW_H

#include <nucleus/types/numericalAliases.h>
#include <string>
#include <functional>
#include <nucleus/core/event_system/event.h>



namespace nucleus {

    struct WindowSpecification {
        u64 width = 800;
        u64 height = 600;

        std::string title = "Nucleus";

        bool vsync = true;

        // future hints can go here
    };


    class IWindow {
    public:
        virtual ~IWindow() = default;

        virtual void SwapBuffers() = 0;

        [[nodiscard]] virtual u64 GetWidth() const = 0;
        [[nodiscard]] virtual u64 GetHeight() const = 0;

        virtual void SetVsync(bool vsync) = 0;

        virtual void Close() = 0;

        [[nodiscard]] virtual void* GetNativeHandle() const = 0;

        virtual void SetEventCallback(std::function<void(IEvent&)> callback) = 0;
    };
}




#endif // NUCLEUS_WINDOW_H