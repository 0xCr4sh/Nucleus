/**
 * @file Application.hpp
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


#ifndef NUCLEUS_APPLICATION
#define NUCLEUS_APPLICATION

#include <Nucleus/Export.hpp>

namespace Nucleus {

    class NUCLEUS_API Application {
    public:
        virtual ~Application() = default;

        virtual void Run() = 0;

    };


    // To be defined by the CLIENT.
    Application* CreateApplication();
    void DestroyApplication(Application* app);


} // Nucleus

#endif