cmake_minimum_required(VERSION 4.1)

project(InjectionClient CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_GENERATOR_PLATFORM x64)

add_library(JVM SHARED IMPORTED)

add_subdirectory(thirdparty/minhook)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui)

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/backends/imgui_impl_win32.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(InjectionClient SHARED
    src/dllmain.cpp
    src/main.cpp
    src/GUI.cpp
    src/modules/Modules.cpp
    src/modules/fly.cpp
    src/utils/jni_utils.cpp
    src/mc/Minecraft.cpp
    src/mc/Player.cpp
    src/hooks/opengl_hook.cpp

    ${IMGUI_SOURCES}
)

target_link_libraries(InjectionClient PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/lib/jvm.lib
    minhook
    opengl32
)

target_include_directories(InjectionClient PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${IMGUI_DIR}
)
