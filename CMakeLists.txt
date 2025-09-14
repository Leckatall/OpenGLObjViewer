cmake_minimum_required(VERSION 3.28)
project(OpenGLObjViewer)

set(CMAKE_CXX_STANDARD 20)



add_executable(OpenGLObjViewer main.cpp
        src/app/window.cpp
        src/app/window.h
        # ImGui files
        include/imgui/imgui.cpp
        include/imgui/imgui_demo.cpp
        include/imgui/imgui_draw.cpp
        include/imgui/imgui_tables.cpp
        include/imgui/imgui_widgets.cpp
        include/imgui/backends/imgui_impl_glfw.cpp
        include/imgui/backends/imgui_impl_opengl3.cpp
        # GLAD
        include/glad/src/glad.c
        # Mine
        src/render/shader_program.cpp
        src/render/shader_program.h
        src/stb_image.cpp
        src/render/camera.cpp
        src/render/camera.h
        src/render/mesh.cpp
        src/render/mesh.h
        src/render/geometry_generator.h
        src/Game/world.cpp
        src/Game/world.h
        src/Game/entity.cpp
        src/Game/entity.h
        src/render/material.cpp
        src/render/material.h
        src/render/texture.cpp
        src/render/texture.h
        src/render/texture_manager.cpp
        src/render/texture_manager.h
        src/render/material_manager.cpp
        src/render/material_manager.h
        src/render/mesh_manager.cpp
        src/render/mesh_manager.h
        src/render/mesh_manager.h
        src/render/renderer.cpp
        src/render/renderer.h
        src/app/application.cpp
        src/app/application.h
        src/render/camera_data.h
)

target_include_directories(OpenGLObjViewer PRIVATE include include/imgui include/glad/include include/glfw/include)
target_link_directories(OpenGLObjViewer PRIVATE include/glfw/lib-mingw-w64)
target_link_libraries(OpenGLObjViewer PRIVATE glfw3 opengl32 gdi32 user32)
