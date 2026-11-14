cmake_minimum_required(VERSION 3.25)

project(Nucleus
        VERSION 1.0.0
        LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SPDLOG_USE_STD_FORMAT OFF CACHE BOOL "" FORCE)
add_subdirectory(external/spdlog)

add_subdirectory(external/glfw)

add_compile_definitions($<$<NOT:$<CONFIG:Debug>>:NUCLEUS_RELEASE>)

add_subdirectory(Nucleus)
add_subdirectory(Sandbox)