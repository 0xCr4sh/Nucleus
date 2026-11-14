add_library(NucleusPlatform STATIC)

target_compile_definitions(NucleusPlatform PRIVATE NUCLEUS_BUILD)

target_include_directories(NucleusPlatform
        PUBLIC
        ${NUCLEUS_ENGINE_PUBLIC_API}
        PRIVATE
        ${NUCLEUS_ENGINE_SRC_ROOT}
)

if(MSVC)
    target_compile_options(NucleusPlatform PRIVATE /W4 /permissive-)
else()
    target_compile_options(NucleusPlatform PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_precompile_headers(NucleusPlatform PRIVATE
        <string>
        <memory>
        <functional>
        <filesystem>
        <GLFW/glfw3.h>
)


target_link_libraries(NucleusPlatform
        PRIVATE
        glfw
        NucleusCore
)

add_subdirectory(glfw)

target_sources(NucleusPlatform
        PRIVATE
        platform.cpp
)