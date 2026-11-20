/**
 * @file EngineRuntime.cpp
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

#include "EngineRuntime.h"
#include <core/logging/LogInternal.h>

#include <core/event_system/Events.h>

namespace nucleus {
    void EngineRuntime::TransferEventToBus(IEvent& e)
    {
        switch (e.GetEventType())
        {
            case EventType::None:
            {
                m_EventBus.Publish<EventNone>(static_cast<EventNone&>(e));
                break;
            }

            case EventType::WindowClose:
            {
                m_EventBus.Publish<WindowCloseEvent>(static_cast<WindowCloseEvent&>(e));
                break;
            }

            case EventType::WindowResize:
            {
                m_EventBus.Publish<WindowResizeEvent>(static_cast<WindowResizeEvent&>(e));
                break;
            }

            case EventType::KeyPressed:
            {
                m_EventBus.Publish<KeyPressedEvent>(static_cast<KeyPressedEvent&>(e));
                break;
            }

            case EventType::KeyReleased:
            {
                m_EventBus.Publish<KeyReleasedEvent>(static_cast<KeyReleasedEvent&>(e));
                break;
            }

            case EventType::KeyRepeated:
            {
                m_EventBus.Publish<KeyRepeatedEvent>(static_cast<KeyRepeatedEvent&>(e));
                break;
            }

            case EventType::MouseButtonPressed:
            {
                m_EventBus.Publish<MouseButtonPressedEvent>(static_cast<MouseButtonPressedEvent&>(e));
                break;
            }

            case EventType::MouseButtonReleased:
            {
                m_EventBus.Publish<MouseButtonReleasedEvent>(static_cast<MouseButtonReleasedEvent&>(e));
                break;
            }

            case EventType::MouseMoved:
            {
                m_EventBus.Publish<MouseMovedEvent>(static_cast<MouseMovedEvent&>(e));
                break;
            }

            case EventType::MouseScrolled:
            {
                m_EventBus.Publish<MouseScrolledEvent>(static_cast<MouseScrolledEvent&>(e));
                break;
            }

            default:
            {
                NUC_CORE_WARN("Unknown event type received: {}", e.GetName());
                m_EventBus.Publish<IEvent>(e);
            }
        }
    }



    EngineRuntime::~EngineRuntime() {
        Shutdown();
    }

    void EngineRuntime::Init() {
        LogInternal::Init();

        m_Platform  = IPlatform::Create();

        m_Application = CreateApplication();

        m_Window = m_Platform->CreateWindow({
            .width  = m_Application->GetHints().WindowWidth,
            .height = m_Application->GetHints().WindowHeight,
            .title  = m_Application->GetHints().WindowTitle,
            .vsync  = m_Application->GetHints().Vsync
        });

        m_Window->SetEventCallback([this](IEvent& e) {
            TransferEventToBus(e);
        });

        m_EventBus.Subscribe<WindowCloseEvent>([&](WindowCloseEvent& e) {
            m_IsRunning = false;
            e.handled = true;
        }, EventPriority::Engine);

        m_Application->OnCreate();

        m_Application->SetContext(GetContext());

        m_IsRunning = true;
    }

    void EngineRuntime::Run() {

        while (m_IsRunning) {
            m_Platform->PollEvents();

            m_Application->OnUpdate();
            m_Application->OnRender();

            m_Window->SwapBuffers();
        }

    }

    void EngineRuntime::Shutdown() {
        if (m_IsTerminated) return;

        DestroyApplication(m_Application);
        m_Application = nullptr;

        m_Window->Close();
        m_Window = nullptr;

        LogInternal::Shutdown();

        m_IsTerminated = true;
    }

    EngineContext EngineRuntime::GetContext() const {
        return {
            .eventbus = &m_EventBus,
        };
    }
} // nucleus