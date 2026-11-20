/**
 * @file EngineRuntime.h
 * @brief Brief explaination goes here...
 * @details Detailed explaination goes here...
 *
 * @author ridham
 * @date 2026-11-14
 *
 * @bug No known bugs
 *
 * @copyright (c) 2026
 */

#ifndef NUCLEUS_ENGINERUNTIME_H
#define NUCLEUS_ENGINERUNTIME_H

#include <nucleus/core/event_system/eventbus.h>
#include <platform/platform.h>
#include <platform/window.h>
#include <memory>
#include <nucleus/Engine/application.h>
#include <nucleus/Engine/EngineContext.h>

namespace nucleus {

    class EngineRuntime final {

    public:
        EngineRuntime() = default;
        ~EngineRuntime();

        void Init();
        void Run();
        void Shutdown();

        EngineContext GetContext() const;

    private:
        void TransferEventToBus(IEvent& e);

        EventBus m_EventBus;
        std::unique_ptr<IPlatform> m_Platform   = nullptr;
        std::unique_ptr<IWindow> m_Window       = nullptr;

        Application* m_Application = nullptr;
        bool m_IsTerminated = false;
        bool m_IsRunning = false;
    };
} // nucleus

#endif //NUCLEUS_ENGINERUNTIME_H
