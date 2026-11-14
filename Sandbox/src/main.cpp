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


namespace {
    class Game : public nucleus::Application
    {
    public:
        Game() : Application({
            .WindowWidth    = 800,
            .WindowHeight   = 600,
            .WindowTitle    = "Nucleus-Sandbox",
            .Vsync          = true
        }) {
            NUC_TRACE("Entered Game");
        }
        ~Game() override {
            NUC_TRACE("Exited Game");
        }

        void OnCreate() override {
            NUC_TRACE("Created Game");
        }

        void OpUpdate() override {

        }
    };
}

nucleus::Application *nucleus::CreateApplication() {
    return new Game();
}

void nucleus::DestroyApplication(Application *app) {
    delete app;
}