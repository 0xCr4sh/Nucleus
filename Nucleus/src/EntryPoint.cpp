/**
 * @file EntryPoint.cpp
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

#include "EntryPoint.h"
#include <Nucleus/Application.hpp>

extern Nucleus::Application* Nucleus::CreateApplication();
extern void Nucleus::DestroyApplication(Application* app);

int main(int argc, char* argv[]) {
    Nucleus::Application* app = Nucleus::CreateApplication();
    app->Run();
    Nucleus::DestroyApplication(app);

    return 0;
}
