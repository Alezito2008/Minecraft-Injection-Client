cmake_minimum_required(VERSION 4.1)

project(InjectionClient CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_GENERATOR_PLATFORM x64)

add_library(JVM SHARED IMPORTED)

add_library(InjectionClient SHARED
    dllmain.cpp
    main.cpp
    functions.cpp
    modules.cpp
)

target_link_libraries(InjectionClient PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/lib/jvm.lib
)

target_include_directories(InjectionClient PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
