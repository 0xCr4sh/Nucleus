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
#include <nucleus/core/application.h>


namespace nucleus {
    struct EngineContext {
        EventBus eventbus;
        std::unique_ptr<IPlatform> platform   = nullptr;
        std::unique_ptr<IWindow> window       = nullptr;
    };

    class EngineRuntime final {

    public:
        EngineRuntime() = default;
        ~EngineRuntime();

        void Init();
        void Run();
        void Shutdown();

        constexpr const EngineContext& GetContext();

    private:
        void TransferEventToBus(IEvent& e);

        EngineContext m_Context;
        Application* m_Application = nullptr;
        bool m_IsTerminated = false;
        bool m_IsRunning = false;
    };
} // nucleus

#endif //NUCLEUS_ENGINERUNTIME_H
