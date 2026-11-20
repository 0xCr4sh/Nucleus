/**
 * @file LayerStack.h
 * @brief Container responsible for managing engine layers and overlays.
 *
 * @details
 * LayerStack provides centralized ownership, ordering, and lifecycle
 * management for Layer instances used by the Nucleus engine.
 *
 * Layers are stored in insertion order, with regular layers positioned
 * before overlays.
 *
 * The stack maintains an insertion boundary that separates regular
 * layers from overlays. New regular layers are inserted at this
 * boundary, while overlays are appended to the end.
 *
 * Structural modifications requested while the stack is locked are
 * deferred and processed once the current operation has completed.
 * This prevents modifications to the underlying container while it
 * is being traversed or otherwise accessed.
 *
 * LayerStack exclusively owns its stored layers through std::unique_ptr.
 *
 * @author Ridham
 * @date 2026-11-19
 *
 * @bug No known bugs
 *
 * @copyright (c) 2026
 */

#ifndef NUCLEUS_LAYERSTACK_H
#define NUCLEUS_LAYERSTACK_H

#include <nucleus/export.h>
#include <memory>
#include <vector>
#include "Layer.h"

namespace nucleus {

    /**
     * @class LayerStack
     * @brief Manages the ownership, ordering, and lifecycle of layers.
     *
     * @details
     * LayerStack acts as the central container for layers participating
     * in the engine's execution lifecycle.
     *
     * It maintains two logical groups:
     *
     * - Regular layers, which are inserted before overlays.
     * - Overlays, which are inserted after all regular layers.
     *
     * The stack owns all registered layers and is responsible for
     * invoking their attachment and detachment callbacks.
     *
     * Structural modifications requested while the stack is locked
     * are deferred until the current operation has completed.
     *
     * @note LayerStack is designed for single-threaded use.
     *       Its locking mechanism prevents reentrant modifications;
     *       it does not provide thread synchronization.
     */
    class NUCLEUS_API LayerStack {
    public:

        /**
         * @brief Underlying container used to store layers.
         *
         * @details
         * Uses unique ownership to ensure that each layer has exactly
         * one owning LayerStack.
         */
        using Container = std::vector<std::unique_ptr<Layer>>;

        /** @brief Mutable iterator for the layer container. */
        using Iterator = Container::iterator;

        /** @brief Constant iterator for the layer container. */
        using ConstIterator = Container::const_iterator;

        /**
         * @brief Constructs an empty LayerStack.
         */
        LayerStack() = default;

        /**
         * @brief Destroys the LayerStack.
         *
         * @details
         * Releases all owned layers and invokes their OnDetach()
         * callbacks before destroying them.
         */
        ~LayerStack();

        /**
         * @brief Inserts a layer into the stack.
         *
         * @details
         * The insertion position depends on the layer's classification:
         *
         * - Regular layers are inserted before all overlays.
         * - Overlays are appended to the end of the stack.
         *
         * The layer's OnAttach() callback is invoked after insertion.
         * If attachment fails, the layer is removed from the stack.
         *
         * If called while the stack is locked, the insertion request
         * is deferred until the current operation has completed.
         *
         * @param layer Unique ownership of the layer being inserted.
         *
         * @note Passing a null pointer is rejected.
         */
        void Push(std::unique_ptr<Layer> layer);

        /**
         * @brief Removes a layer from the stack.
         *
         * @details
         * Searches for the specified layer and removes it if present.
         * The layer's OnDetach() callback is invoked before destruction.
         *
         * If called while the stack is locked, the removal request
         * is deferred until the current operation has completed.
         *
         * @param layer Non-owning pointer identifying the layer to remove.
         *
         * @note The pointer must identify a layer currently owned by
         *       this LayerStack.
         */
        void Pop(Layer* layer);

        /**
         * @brief Releases all layers owned by the stack.
         *
         * @details
         * Invokes OnDetach() on every currently registered layer before
         * destroying them and clearing the internal containers.
         *
         * Pending insertion and removal requests are discarded.
         *
         * @note This operation is intended for stack cleanup and shutdown.
         */
        void Free();

        /**
         * @brief Returns a constant iterator to the first layer.
         *
         * @details
         * Provides read-only access to the beginning of the layer container.
         * The returned iterator does not allow modification of the
         * stored unique pointers through the iterator.
         *
         * @return ConstIterator pointing to the beginning of the container.
         */
        [[nodiscard]] ConstIterator begin() const;

        /**
         * @brief Returns a constant iterator past the last layer.
         *
         * @details
         * Provides read-only access to the end of the layer container.
         * This iterator represents the position after the last layer and
         * must not be dereferenced.
         *
         * @return ConstIterator pointing past the end of the container.
         */
        [[nodiscard]] ConstIterator end() const;

        /**
         * @brief Updates all layers currently in the stack.
         *
         * @details
         * Iterates through the layer container and invokes OnUpdate()
         * on each layer in insertion order.
         *
         * Structural modifications requested during this iteration
         * are queued and processed after iteration completes.
         *
         * @param deltaTime Elapsed time since the previous update,
         *                  expressed in seconds.
         */
        void UpdateLayers(f32 deltaTime);

        /**
         * @brief Renders all layers currently in the stack.
         *
         * @details
         * Iterates through the layer container and invokes OnRender()
         * on each layer in insertion order.
         *
         * Regular layers are rendered before overlays, allowing overlays
         * to render their contents on top of regular layers.
         *
         * @note This function does not perform rendering initialization
         *       or manage the rendering context. Those responsibilities
         *       belong to the engine runtime and rendering subsystem.
         */
        void RenderLayers();

    private:

        /**
         * @brief Processes all deferred layer operations.
         *
         * @details
         * Executes pending insertion and removal requests once the stack
         * is no longer locked.
         *
         * Operations generated by lifecycle callbacks during processing
         * are collected and processed in subsequent batches.
         */
        void ProcessPendingOperations();

        /**
         * @brief Inserts a layer directly into the underlying container.
         *
         * @details
         * Performs the insertion and attachment operation without
         * deferring the request.
         *
         * @param layer Unique ownership of the layer being inserted.
         */
        void PushImmediate(std::unique_ptr<Layer> layer);

        /**
         * @brief Removes a layer directly from the underlying container.
         *
         * @details
         * Performs the removal and detachment operation without
         * deferring the request.
         *
         * @param layer Non-owning pointer identifying the layer to remove.
         */
        void PopImmediate(Layer* layer);

        /**
         * @brief Indicates whether the stack is currently locked.
         *
         * @details
         * Prevents reentrant structural modifications while the stack
         * is traversing its layers or performing another protected operation.
         *
         * Requests made while locked are deferred until it is unlocked.
         *
         * @note This is not a thread synchronization primitive.
         */
        bool m_IsLocked = false;

        /** @brief Container exclusively owning all registered layers. */
        Container m_Layers;

        /**
         * @brief Index separating regular layers from overlays.
         *
         * @details
         * All elements before this index are regular layers.
         * All elements from this index onwards are overlays.
         *
         * New regular layers are inserted at this position, and the
         * index is adjusted whenever regular layers are inserted or removed.
         */
        u32 m_LayerInsertIndex = 0;

        /**
         * @brief Layers awaiting insertion into the stack.
         *
         * @details
         * Stores ownership of layers whose insertion has been requested
         * while the stack is locked.
         */
        Container m_PendingPush;

        /**
         * @brief Layers awaiting removal from the stack.
         *
         * @details
         * Stores non-owning pointers identifying layers whose removal
         * has been requested while the stack is locked.
         *
         * The actual ownership remains with m_Layers until removal
         * is processed.
         */
        std::vector<Layer*> m_PendingPop;
    };

} // namespace nucleus

#endif // NUCLEUS_LAYERSTACK_H