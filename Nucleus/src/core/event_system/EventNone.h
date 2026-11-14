
/**
 * @file eventnone.h
 * @brief Defines the EventNone sentinel event.
 *
 * @details
 * Provides a concrete representation of the absence of a specific
 * event. Primarily useful as a default or placeholder event type.
 *
 * EventNone does not represent an actual application, input, or
 * window event.
 *
 * @author Ridham
 * @date 2026-11-12
 *
 * @bug No known bugs.
 *
 * @copyright (c) 2026 Ridham
 */

#ifndef NUCLEUS_EVENTNONE_H
#define NUCLEUS_EVENTNONE_H

#include "../../../include/nucleus/core/event_system/event.h"
#include <nucleus/types/numericalAliases.h>
#include <nucleus/export.h>

namespace nucleus
{

    /**
     * @brief Represents the absence of a specific event.
     *
     * @details
     * A concrete Event implementation associated with EventType::None.
     * It carries no additional event-specific information.
     */
    class NUCLEUS_API EventNone final : public IEvent
    {
    public:

        ~EventNone() override = default;

        /**
         * @brief Retrieves the event type.
         *
         * @return EventType::None.
         */
        [[nodiscard]] EventType GetEventType() const override;

        /**
         * @brief Retrieves the event name.
         *
         * @return Null-terminated name of this event.
         */
        [[nodiscard]] const char* GetName() const override;

        /**
         * @brief Retrieves the event categories.
         *
         * @return EventCategoryNone.
         */
        [[nodiscard]] u32 GetCategoryFlags() const override;
    };

}

#endif // NUCLEUS_EVENTNONE_H
