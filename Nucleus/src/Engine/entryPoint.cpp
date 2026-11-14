/**
* @file entryPoint.cpp
 * @brief Defines the program entry point for Nucleus applications.
 *
 * @details
 * This file provides the main() function used to launch applications
 * built with the Nucleus engine.
 *
 * The entry point is responsible for coordinating the application's
 * startup, execution, and shutdown lifecycle.
 *
 * By providing its own entry point, Nucleus manages the application's
 * execution lifecycle, allowing clients to focus on implementing their
 * application rather than writing the startup and shutdown logic.
 *
 * @author Ridham
 * @date 2026-11-09
 *
 * @bug No known bugs.
 *
 * @copyright (c) 2026 Ridham
 */

#include <Engine/Runtime/EngineRuntime.h>

int main(int argc, char* argv[]) {
    nucleus::EngineRuntime runtime{};

    runtime.Init();
    runtime.Run();
    runtime.Shutdown();

    return 0;
}