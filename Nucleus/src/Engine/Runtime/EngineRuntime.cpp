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
#include <nucleus/core/application.h>
#include <core/logging/LogInternal.h>

#include <core/event_system/Events.h>

namespace nucleus {
    void EngineRuntime::TransferEventToBus(IEvent& e)
    {
        switch (e.GetEventType())
        {
            case EventType::None:
            {
                m_Context.eventbus.Publish<EventNone>(static_cast<EventNone&>(e));
                break;
            }

            case EventType::WindowClose:
            {
                m_Context.eventbus.Publish<WindowCloseEvent>(static_cast<WindowCloseEvent&>(e));
                break;
            }

            case EventType::WindowResize:
            {
                m_Context.eventbus.Publish<WindowResizeEvent>(static_cast<WindowResizeEvent&>(e));
                break;
            }

            case EventType::KeyPressed:
            {
                m_Context.eventbus.Publish<KeyPressedEvent>(static_cast<KeyPressedEvent&>(e));
                break;
            }

            case EventType::KeyReleased:
            {
                m_Context.eventbus.Publish<KeyReleasedEvent>(static_cast<KeyReleasedEvent&>(e));
                break;
            }

            case EventType::KeyRepeated:
            {
                m_Context.eventbus.Publish<KeyRepeatedEvent>(static_cast<KeyRepeatedEvent&>(e));
                break;
            }

            case EventType::MouseButtonPressed:
            {
                m_Context.eventbus.Publish<MouseButtonPressedEvent>(static_cast<MouseButtonPressedEvent&>(e));
                break;
            }

            case EventType::MouseButtonReleased:
            {
                m_Context.eventbus.Publish<MouseButtonReleasedEvent>(static_cast<MouseButtonReleasedEvent&>(e));
                break;
            }

            case EventType::MouseMoved:
            {
                m_Context.eventbus.Publish<MouseMovedEvent>(static_cast<MouseMovedEvent&>(e));
                break;
            }

            case EventType::MouseScrolled:
            {
                m_Context.eventbus.Publish<MouseScrolledEvent>(static_cast<MouseScrolledEvent&>(e));
                break;
            }

            default:
            {
                NUC_CORE_WARN("Unknown event type received: {}", e.GetName());
                m_Context.eventbus.Publish<IEvent>(e);
            }
        }
    }



    EngineRuntime::~EngineRuntime() {
        Shutdown();
    }

    void EngineRuntime::Init() {
        LogInternal::Init();

        m_Context.platform  = IPlatform::Create();

        m_Application = CreateApplication();

        m_Context.window = m_Context.platform->CreateWindow({
            .width  = m_Application->GetHints().WindowWidth,
            .height = m_Application->GetHints().WindowHeight,
            .title  = m_Application->GetHints().WindowTitle,
            .vsync  = m_Application->GetHints().Vsync
        });

        m_Context.window->SetEventCallback([this](IEvent& e) {
            TransferEventToBus(e);
        });

        m_Application->OnCreate();

        m_Context.eventbus.Subscribe<WindowCloseEvent>([&](WindowCloseEvent& e) {
            m_IsRunning = false;
            e.handled = true;
        }, EventPriority::Engine);

        m_IsRunning = true;
    }

    void EngineRuntime::Run() {

        while (m_IsRunning) {
            m_Context.platform->PollEvents();

            m_Application->OpUpdate();

            m_Context.window->SwapBuffers();
        }

    }

    void EngineRuntime::Shutdown() {
        if (m_IsTerminated) return;

        DestroyApplication(m_Application);
        m_Application = nullptr;

        m_Context.window->Close();
        m_Context.window = nullptr;

        LogInternal::Shutdown();

        m_IsTerminated = true;
    }

    constexpr const EngineContext &EngineRuntime::GetContext() {
        return m_Context;
    }
} // nucleus