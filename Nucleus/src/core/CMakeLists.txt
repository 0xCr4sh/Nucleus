add_library(NucleusCore STATIC)

target_compile_definitions(NucleusCore PRIVATE NUCLEUS_BUILD)

target_include_directories(NucleusCore
        PUBLIC
        ${NUCLEUS_ENGINE_PUBLIC_API}
        PRIVATE
        ${NUCLEUS_ENGINE_SRC_ROOT}
)

if(MSVC)
    target_compile_options(NucleusCore PRIVATE /W4 /permissive-)
else()
    target_compile_options(NucleusCore PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_subdirectory(event_system)
add_subdirectory(logging)

target_precompile_headers(NucleusCore PRIVATE
        <vector>
        <string>
        <unordered_map>
        <spdlog/spdlog.h>
        <spdlog/sinks/stdout_color_sinks.h>
        <format>
        <string_view>
        <utility>
)

target_link_libraries(NucleusCore
        PRIVATE
        spdlog::spdlog
)