
/**
 * @file Layer.h
 * @brief Base abstraction for layers managed by the Nucleus engine.
 *
 * @details
 * A Layer represents an independently managed unit of engine or
 * application functionality.
 *
 * Layers provide lifecycle callbacks and execution hooks that allow
 * the engine to initialize, update, render, and clean up functionality
 * in a structured manner.
 *
 * Layers are owned and managed by the LayerStack. Their execution
 * order is determined by their position within that stack.
 *
 * A layer can be classified as either a regular layer or an overlay.
 * Regular layers are inserted before overlays, allowing overlays to
 * execute after the regular layers.
 *
 * @author ridham
 * @date 2026-11-19
 *
 * @bug No known bugs
 *
 * @copyright (c) 2026
 */

#ifndef NUCLEUS_LAYER_H
#define NUCLEUS_LAYER_H

#include <nucleus/types/numericalAliases.h>
#include <nucleus/export.h>

namespace nucleus {

    /**
     * @class Layer
     * @brief Base class for engine and application layers.
     *
     * @details
     * Provides a common interface for functionality that needs to
     * participate in the engine's update and rendering lifecycle.
     *
     * Derive from this class to implement custom layers.
     *
     * The LayerStack takes ownership of layers and manages their
     * attachment and detachment lifecycle.
     */
    class NUCLEUS_API Layer {
    public:

        /**
         * @enum Type
         * @brief Specifies the classification of a layer.
         *
         * @details
         * The classification determines where a layer is inserted
         * within the LayerStack.
         */
        enum class Type : u8 {

            /**
             * @brief Regular layer.
             *
             * Inserted before all overlays in the LayerStack.
             */
            REGULAR = 0,

            /**
             * @brief Overlay layer.
             *
             * Inserted after all regular layers in the LayerStack.
             * Commonly used for debugging interfaces and editor UI.
             */
            OVERLAY
        };

        /**
         * @brief Constructs a layer with the specified classification.
         *
         * @param type Classification assigned to this layer.
         */
        explicit Layer(Type type)
            : m_Type(type) {}

        /**
         * @brief Virtual destructor.
         *
         * @details
         * Ensures proper destruction of derived layer instances
         * through a base-class pointer.
         */
        virtual ~Layer() = default;

        /**
         * @brief Retrieves the classification of this layer.
         *
         * @return The layer's Type.
         */
        [[nodiscard]] constexpr Type GetType() const {
            return m_Type;
        }

        /**
         * @brief Called once per engine update iteration.
         *
         * @details
         * Provides the layer with an opportunity to perform
         * time-dependent logic, simulation, and other update tasks.
         *
         * @param deltaTime Elapsed time since the previous update,
         *                  expressed in seconds.
         */
        virtual void OnUpdate(f32 deltaTime) {}

        /**
         * @brief Called when the layer should render its contents.
         *
         * @details
         * Provides the layer with an opportunity to submit rendering
         * commands or perform other rendering-related operations.
         */
        virtual void OnRender() {}

        /**
         * @brief Called when the layer is attached to a LayerStack.
         *
         * @details
         * Intended for initialization and acquisition of resources
         * required by the layer.
         */
        virtual void OnAttach() {}

        /**
         * @brief Called when the layer is detached from a LayerStack.
         *
         * @details
         * Intended for releasing resources and performing cleanup
         * associated with the layer's attachment.
         */
        virtual void OnDetach() {}

    protected:

        /** @brief Classification assigned to this layer. */
        const Type m_Type;
    };

} // namespace nucleus

#endif // NUCLEUS_LAYER_H
