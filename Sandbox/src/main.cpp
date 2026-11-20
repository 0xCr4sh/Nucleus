/**
 * @file main.cpp
 * @brief Brief explaination goes here...
 * @details Detailed explaination goes here...
 *
 * @author ridham
 * @date 2026-11-09
 *
 * @bug No known bugs
 *
 * @copyright (c) 2026
 */

#include <nucleus/nucleus.h>

#include "nucleus/Engine/Layers/Layer.h"

namespace {
    class GameplayLayer final : public nucleus::Layer {
    public:
        GameplayLayer() : Layer(Type::REGULAR) {}

        void OnAttach() override {
            NUC_TRACE("Created GameplayLayer {}", static_cast<void*>(this));
        }

        void OnDetach() override {
            NUC_TRACE("Deleted GameplayLayer {}", static_cast<void*>(this));
        }
    };

    class Game final : public nucleus::Application
    {
    public:
        void OnCreate() override {
            NUC_TRACE("Created Game");
            m_LayerStack.Push(std::make_unique<GameplayLayer>());
        }

        void OnShutdown() override {
            NUC_TRACE("Shutting Down Game");
        }

        void OnUpdate() override {

        }

        void OnRender() override {

        }

    };
}

SET_NUCLEUS_APPLICATION(Game);