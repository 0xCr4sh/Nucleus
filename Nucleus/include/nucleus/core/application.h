
/**
 * @file application.h
 * @brief Declares the base Application interface and application factory functions.
 *
 * @details
 * Provides the core Application interface used by programs built
 * with the Nucleus engine.
 *
 * The Application class acts as the base class for client-defined
 * applications. Clients must derive from this class and implement
 * its pure virtual Run() function to define their application's
 * execution logic.
 *
 * Nucleus uses an application factory mechanism to obtain an
 * instance of the client-defined Application implementation.
 * The client is responsible for defining CreateApplication(),
 * while DestroyApplication() provides a corresponding mechanism
 * for releasing the created instance.
 *
 * This separation allows Nucleus to control the application's
 * execution lifecycle without requiring knowledge of the
 * client's concrete Application implementation.
 *
 * @author Ridham
 * @date 2026-11-09
 *
 * @bug No known bugs.
 *
 * @copyright (c) 2026 Ridham
 */

#ifndef NUCLEUS_APPLICATION_H
#define NUCLEUS_APPLICATION_H

#include "../export.h"
#include "../types/numericalAliases.h"
#include <string>

namespace nucleus {
    struct NUCLEUS_API ApplicationHints {
        u64 WindowWidth = 800;
        u64 WindowHeight = 600;

        std::string WindowTitle = "Nucleus";

        bool Vsync = true;
    };

    /**
     * @class Application
     * @brief Base interface for client-defined applications.
     *
     * @details
     * Applications built with Nucleus must provide their own
     * implementation of this class.
     *
     * The Application interface defines the entry point into
     * the client's application logic through Run().
     *
     * Nucleus manages the creation, execution, and destruction
     * of the Application instance through its application
     * factory and entry-point infrastructure.
     */
    class NUCLEUS_API Application {
    public:

        explicit Application(const ApplicationHints& hints)
            : m_Hints(hints) {}

        constexpr const ApplicationHints& GetHints() {
            return m_Hints;
        }

        /**
         * @brief Virtual destructor.
         *
         * @details
         * Ensures that derived Application instances are
         * correctly destroyed when released through an
         * Application pointer.
         */
        virtual ~Application() = default;

        virtual void OnCreate() = 0;

        virtual void OpUpdate() = 0;

    protected:
        ApplicationHints m_Hints;

    };


    /**
     * @brief Creates the client-defined Application instance.
     *
     * @details
     * This function must be implemented by the client application.
     *
     * Nucleus invokes it during application startup to obtain
     * an instance of the client's concrete Application class.
     *
     * @return Pointer to the newly created Application instance.
     *
     * @note The returned instance is expected to be destroyed
     *       through DestroyApplication().
     */
    Application* CreateApplication();

    /**
     * @brief Destroys a client-defined Application instance.
     *
     * @details
     * This function must be implemented by the client application.
     *
     * Nucleus invokes it during application shutdown to release
     * the Application instance previously returned by
     * CreateApplication().
     *
     * @param app Pointer to the Application instance to destroy.
     *
     * @note The implementation must correctly release the
     *       concrete derived Application object.
     */
    void DestroyApplication(Application* app);
} // namespace Nucleus

#endif // NUCLEUS_APPLICATION_H