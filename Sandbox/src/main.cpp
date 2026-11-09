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

#include <print>
#include <Nucleus/Application.hpp>

class Game : public Nucleus::Application
{
public:
    Game() {
        std::print("Game started\n");
    }
    ~Game() override {
        std::print("Game destroyed\n");
    }

    void Run() override {
        std::print("Game running\n");
    }
};

Nucleus::Application *Nucleus::CreateApplication() {
    return new Game();
}

void Nucleus::DestroyApplication(Application *app) {
    delete app;
}