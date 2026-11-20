/**
 * @file EngineContext.h
 * @brief Brief explaination goes here...
 * @details Detailed explaination goes here...
 *
 * @author ridham
 * @date 2026-11-15
 *
 * @bug No known bugs
 *
 * @copyright (c) 2026
 */


#ifndef NUCLEUS_ENGINECONTEXT_H
#define NUCLEUS_ENGINECONTEXT_H

#include <nucleus/core/event_system/eventbus.h>

namespace nucleus {
    struct EngineContext {
        const EventBus*     eventbus    = nullptr;
    };
}

#endif // NUCLEUS_ENGINECONTEXT_H