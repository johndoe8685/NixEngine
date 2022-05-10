cmake_minimum_required(VERSION 3.0)

project(deneme)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)
set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)
set(PROJECT_VENDOR_DIR ${PROJECT_DIR}/vendor)

set(PROJECT_SOURCES
        ${PROJECT_SOURCE_DIR}/vendor/glad.c
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/Application.cpp
        ${PROJECT_SOURCE_DIR}/window.cpp
        ${PROJECT_SOURCE_DIR}/shader.cpp
        ${PROJECT_SOURCE_DIR}/vertexBuffer.cpp
        ${PROJECT_SOURCE_DIR}/vertexArray.cpp
        ${PROJECT_SOURCE_DIR}/vertexBufferLayout.cpp
        ${PROJECT_SOURCE_DIR}/texture.cpp
        ${PROJECT_SOURCE_DIR}/renderer.cpp
)

add_subdirectory(${PROJECT_VENDOR_DIR}/glm)
add_subdirectory(${PROJECT_VENDOR_DIR}/spdlog)

set(PROJECT_HEADERS
        ${PROJECT_INCLUDE_DIR}/vendor/glad/glad.h
        ${PROJECT_INCLUDE_DIR}/vendor/stb/stb_image.h
        ${PROJECT_INCLUDE_DIR}/Application.h
        ${PROJECT_INCLUDE_DIR}/window.h
        ${PROJECT_INCLUDE_DIR}/shader.h
        ${PROJECT_INCLUDE_DIR}/vertexBuffer.h
        ${PROJECT_INCLUDE_DIR}/vertexArray.h
        ${PROJECT_INCLUDE_DIR}/vertexBufferLayout.h
        ${PROJECT_INCLUDE_DIR}/texture.h
        ${PROJECT_INCLUDE_DIR}/renderer.h
)

find_package(glfw3 3.3 REQUIRED)

include_directories(${PROJECT_INCLUDE_DIR})
file(COPY ${PROJECT_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
set(GCC_COVERAGE_LINK_FLAGS "-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl ")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
target_link_libraries(${PROJECT_NAME} glfw)
