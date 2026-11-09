add_library(Nucleus SHARED)

target_sources(Nucleus PRIVATE
        src/Application.cpp
        src/EntryPoint.cpp
)

target_include_directories(Nucleus
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include

        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_definitions(Nucleus
        PRIVATE NUCLEUS_BUILD
)