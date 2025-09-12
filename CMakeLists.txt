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
        )

target_include_directories(OpenGLObjViewer PRIVATE include/imgui include/glad/include include/glfw/include)
target_link_directories(OpenGLObjViewer PRIVATE include/glfw/lib-mingw-w64)
target_link_libraries(OpenGLObjViewer PRIVATE glfw3 opengl32 gdi32 user32)
