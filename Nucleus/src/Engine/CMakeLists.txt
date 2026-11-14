add_library(NucleusEngine STATIC)

target_compile_definitions(NucleusEngine PRIVATE NUCLEUS_BUILD)

target_include_directories(NucleusEngine
        PUBLIC
        ${NUCLEUS_ENGINE_PUBLIC_API}
        PRIVATE
        ${NUCLEUS_ENGINE_SRC_ROOT}
)

add_subdirectory(Runtime)

if(MSVC)
    target_compile_options(NucleusEngine PRIVATE /W4 /permissive-)
else()
    target_compile_options(NucleusEngine PRIVATE -Wall -Wextra -Wpedantic)
endif()

#target_precompile_headers(NucleusEngine PRIVATE
#        <vector>
#        <string>
#        <unordered_map>
#        <spdlog/spdlog.h>
#        <spdlog/sinks/stdout_color_sinks.h>
#)

target_sources(NucleusEngine
        PRIVATE
        entryPoint.cpp
)

target_link_libraries(NucleusEngine
        PRIVATE
        NucleusCore
        NucleusPlatform
)