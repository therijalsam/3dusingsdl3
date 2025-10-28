cmake_minimum_required(VERSION 3.20)
project(SDL3_Render3D LANGUAGES CXX)

# Modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable warnings
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ---- Find SDL3 ----
find_package(SDL3 REQUIRED CONFIG PATHS /usr/local/lib/cmake/SDL3)


# ---- Define executable ----
add_executable(sdl3render
        src/main.cpp
        include/sdl3_renderer/Camera.hpp
        include/sdl3_renderer/IMeshLoader.hpp
        include/sdl3_renderer/IProjector.hpp
        include/sdl3_renderer/Mat4.hpp
        include/sdl3_renderer/Mesh.hpp
        include/sdl3_renderer/OBJMeshLoader.hpp
        include/sdl3_renderer/Renderer3D.hpp
        include/sdl3_renderer/Vec3.hpp
        include/sdl3_renderer/Projector.hpp
        include/sdl3_renderer/CameraController.hpp
        include/sdl3_renderer/GridRenderer.hpp
        include/sdl3_renderer/ModelTransformer.hpp
)

# ---- Include directories ----
target_include_directories(sdl3render PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

# ---- Link SDL3 ----
target_link_libraries(sdl3render PRIVATE SDL3::SDL3)

# ---- Copy assets ----
add_custom_command(TARGET sdl3render POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
)
