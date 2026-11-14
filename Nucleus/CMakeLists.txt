set(NUCLEUS_ENGINE_PUBLIC_API
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(NUCLEUS_ENGINE_SRC_ROOT
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(src/core)
add_subdirectory(src/platform)
add_subdirectory(src/Engine)

add_library(NucleusGameEngine INTERFACE)

target_link_libraries(NucleusGameEngine
        INTERFACE
        NucleusCore
        NucleusPlatform
        NucleusEngine
)