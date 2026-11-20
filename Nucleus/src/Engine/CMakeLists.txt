add_library(NucleusEngine STATIC)

target_compile_definitions(NucleusEngine PRIVATE NUCLEUS_BUILD)

target_include_directories(NucleusEngine
        PUBLIC
        ${NUCLEUS_ENGINE_PUBLIC_API}
        PRIVATE
        ${NUCLEUS_ENGINE_SRC_ROOT}
)

add_subdirectory(Runtime)
add_subdirectory(Layer)

if(MSVC)
    target_compile_options(NucleusEngine PRIVATE /W4 /permissive-)
else()
    target_compile_options(NucleusEngine PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_precompile_headers(NucleusEngine PRIVATE
        <vector>
        <memory>
        <algorithm>
)

target_sources(NucleusEngine
        PRIVATE
        entryPoint.cpp
)

target_link_libraries(NucleusEngine
        PRIVATE
        NucleusCore
        NucleusPlatform
)