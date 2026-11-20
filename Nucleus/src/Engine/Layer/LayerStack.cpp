/**
* @file LayerStack.cpp
 * @brief Implementation of the LayerStack class.
 *
 * @details
 * Provides the implementation for managing and maintaining an ordered
 * collection of layers and overlays within the Nucleus engine.
 *
 * The LayerStack owns its layers through std::unique_ptr and maintains
 * regular layers separately from overlays. Regular layers are inserted
 * before overlays, preserving their respective ordering.
 *
 * Layer lifecycle callbacks are invoked when layers are attached or
 * detached. During layer traversal or lifecycle callbacks, stack
 * modifications are deferred and processed once the stack is unlocked.
 *
 * An RAII lock guard protects traversal and mutation operations from
 * reentrant modifications while ensuring the lock is released safely,
 * including when exceptions occur.
 *
 * @author Ridham
 * @date 2026-11-19
 *
 * @bug No known bugs
 */

#include <nucleus/Engine/Layers/LayerStack.h>
#include <algorithm>
#include <core/logging/LogInternal.h>

namespace {
    class LayerStackLockGuard {
    public:
        explicit LayerStackLockGuard(bool& locked)
            : m_Locked(locked) {
            m_Locked = true;
        }

        ~LayerStackLockGuard() {
            m_Locked = false;
        }

        LayerStackLockGuard(const LayerStackLockGuard&) = delete;
        LayerStackLockGuard& operator=(const LayerStackLockGuard&) = delete;

    private:
        bool& m_Locked;
    };

    #define LOCK LayerStackLockGuard lock(m_IsLocked);
}

namespace nucleus {
    LayerStack::~LayerStack() {
        Free();
    }

    void LayerStack::Free() {
        LOCK
        m_LayerInsertIndex = 0;

        for (auto& layer : m_Layers) {
            try {
                layer->OnDetach();
            }
            catch (...) {
                NUC_CORE_ERR("Layer {} threw an exception in its OnDetach()", static_cast<void*>(layer.get()));
            }
        }

        m_Layers.clear();
        m_PendingPush.clear();
        m_PendingPop.clear();
    }

    LayerStack::ConstIterator LayerStack::begin() const {
        return m_Layers.cbegin();
    }

    LayerStack::ConstIterator LayerStack::end() const {
        return m_Layers.cend();
    }

    void LayerStack::PushImmediate(std::unique_ptr<Layer> layer) {
        if (layer == nullptr) {
            NUC_CORE_ERR("LayerStack::PushImmediate() nullptr passed to LayerStack with address {}", static_cast<const void*>(this));
            return;
        }

        if (layer->GetType() == Layer::Type::REGULAR) {
            auto it = m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, std::move(layer));
            m_LayerInsertIndex++;

            try {
                it->get()->OnAttach();
            }
            catch (...) {
                NUC_CORE_ERR("LayerStack::Push() | Layer {} has thrown an exception in Layer::onAttach. Cannot push layer", static_cast<void*>(it->get()));
                it = m_Layers.erase(it);
                --m_LayerInsertIndex;
            }
        }
        else if (layer->GetType() == Layer::Type::OVERLAY) {
            auto it = m_Layers.emplace(m_Layers.end(), std::move(layer));

            try {
                it->get()->OnAttach();
            }
            catch (...) {
                NUC_CORE_ERR("LayerStack::Push() | Layer {} has thrown an exception in Layer::onAttach. Cannot push layer", static_cast<void*>(it->get()));
                it = m_Layers.erase(it);
            }
        }
        else {
            NUC_CORE_ERR("Failed to push layer in LayerStack {}. Unknown Layer::Type of layer {}.", static_cast<void*>(this), static_cast<void*>(layer.get()));
        }
    }

    void LayerStack::Push(std::unique_ptr<Layer> layer) {
        if (layer == nullptr) {
            NUC_CORE_ERR("LayerStack::Push() nullptr passed to LayerStack with address {}", static_cast<const void*>(this));
            return;
        }

        if (m_IsLocked) {
            m_PendingPush.push_back(std::move(layer));
            return;
        }

        {
            LOCK
            PushImmediate(std::move(layer));
        }

        ProcessPendingOperations();
    }

    void LayerStack::PopImmediate(Layer *layer) {
        if (layer == nullptr) {
            NUC_CORE_ERR("LayerStack::PopImmediate() nullptr passed to LayerStack with address {}", static_cast<const void*>(this));
            return;
        }

        bool exists = std::ranges::any_of(m_Layers, [layer](const auto& ptr) {
            return ptr.get() == layer;
        });

        if (!exists) {
            return;
        }

        if (layer->GetType() == Layer::Type::REGULAR) {
            auto it = std::find_if(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex,
                [layer](const std::unique_ptr<Layer>& listLayer){
                        return listLayer.get() == layer;
                });

            if (it != m_Layers.begin() + m_LayerInsertIndex) {
                try {
                    it->get()->OnDetach();
                }
                catch (...) {
                    NUC_CORE_ERR("Layer {} threw an exception in its OnDetach()", static_cast<void*>(it->get()));
                }
                m_Layers.erase(it);
                m_LayerInsertIndex--;
            }
        }
        else if (layer->GetType() == Layer::Type::OVERLAY) {
            auto it = std::find_if(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(),
            [layer](const std::unique_ptr<Layer>& listOverlay){
                    return listOverlay.get() == layer;
                });

            if (it != m_Layers.end()) {
                try {
                    it->get()->OnDetach();
                }
                catch (...) {
                    NUC_CORE_ERR("Layer {} threw an exception in its OnDetach()", static_cast<void*>(it->get()));
                }
                m_Layers.erase(it);

            }
        }
    }

    void LayerStack::Pop(Layer* layer) {
        if (layer == nullptr) {
            NUC_CORE_ERR("LayerStack::Pop() nullptr passed to LayerStack with address {}", static_cast<const void*>(this));
            return;
        }

        if (m_IsLocked) {
            m_PendingPop.push_back(layer);
            return;
        }

        {
            LOCK
            PopImmediate(layer);
        }

        ProcessPendingOperations();
    }

    void LayerStack::UpdateLayers(f32 deltaTime) {
        if (m_IsLocked) {
            NUC_CORE_INFO("Cannot update LayerStack. LayerStack is locked.");
            return;
        }

        {
            LOCK
            for (auto& layer : m_Layers) {
                try {
                    layer->OnUpdate(deltaTime);
                }
                catch (...) {
                    NUC_CORE_ERR("Layer {} threw an exception during update", static_cast<void*>(layer.get()));
                }
            }
        }

        ProcessPendingOperations();
    }


    void LayerStack::RenderLayers() {
        if (m_IsLocked) {
            NUC_CORE_INFO("Cannot render LayerStack. LayerStack is locked.");
            return;
        }

        {
            LOCK
            for (auto& layer : m_Layers) {
                try {
                    layer->OnRender();
                }
                catch (...) {
                    NUC_CORE_ERR("Layer {} threw an exception during render", static_cast<void*>(layer.get()));
                }
            }
        }

        ProcessPendingOperations();
    }


    void LayerStack::ProcessPendingOperations() {
        if (m_IsLocked)
            return;

        LOCK

        while (!m_PendingPush.empty() || !m_PendingPop.empty()) {
            auto pendingPush = std::move(m_PendingPush);
            auto pendingPop = std::move(m_PendingPop);

            m_PendingPush.clear();
            m_PendingPop.clear();

            for (auto& layer : pendingPush) {
                PushImmediate(std::move(layer));
            }

            for (auto* layer : pendingPop) {
                PopImmediate(layer);
            }
        }
    }
} // nucleus