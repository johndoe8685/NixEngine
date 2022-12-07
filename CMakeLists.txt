cmake_minimum_required(VERSION 3.0)

project(NixEngine)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)



set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)
set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)
set(PROJECT_VENDOR_DIR ${PROJECT_DIR}/vendor)

add_subdirectory(${PROJECT_DIR}/vendor/glfw-3.3.8)

set(PROJECT_SOURCES
        ${PROJECT_SOURCE_DIR}/vendor/glad.c
        ${PROJECT_SOURCE_DIR}/vendor/stb_image.cpp
        ${PROJECT_SOURCE_DIR}/vendor/imGui/imgui.cpp
        ${PROJECT_SOURCE_DIR}/vendor/imGui/imgui_draw.cpp
        ${PROJECT_SOURCE_DIR}/vendor/imGui/imgui_tables.cpp
        ${PROJECT_SOURCE_DIR}/vendor/imGui/imgui_widgets.cpp
        ${PROJECT_SOURCE_DIR}/vendor/imGui/imgui_demo.cpp
        ${PROJECT_SOURCE_DIR}/vendor/imGui/imgui_impl_glfw.cpp
        ${PROJECT_SOURCE_DIR}/vendor/imGui/imgui_impl_opengl3.cpp
        ${PROJECT_SOURCE_DIR}/Light/light.cpp
        ${PROJECT_SOURCE_DIR}/Light/ambientlight.cpp
        ${PROJECT_SOURCE_DIR}/Light/directionallight.cpp
        ${PROJECT_SOURCE_DIR}/Light/positionallight.cpp
        ${PROJECT_SOURCE_DIR}/Light/pointlight.cpp
        ${PROJECT_SOURCE_DIR}/Light/spotlight.cpp
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/Application.cpp
        ${PROJECT_SOURCE_DIR}/window.cpp
        ${PROJECT_SOURCE_DIR}/system.cpp
        ${PROJECT_SOURCE_DIR}/directory.cpp
        ${PROJECT_SOURCE_DIR}/debugger.cpp
        ${PROJECT_SOURCE_DIR}/shader.cpp
        ${PROJECT_SOURCE_DIR}/texture.cpp
        ${PROJECT_SOURCE_DIR}/renderer.cpp
        ${PROJECT_SOURCE_DIR}/mesh.cpp
        ${PROJECT_SOURCE_DIR}/camera.cpp
        ${PROJECT_SOURCE_DIR}/material.cpp
        ${PROJECT_SOURCE_DIR}/model.cpp
        ${PROJECT_SOURCE_DIR}/debugconsole.cpp
        ${PROJECT_SOURCE_DIR}/scene.cpp
        ${PROJECT_SOURCE_DIR}/assetmanager.cpp
        ${PROJECT_SOURCE_DIR}/shadermanager.cpp
)

set(PROJECT_HEADERS
        ${PROJECT_INCLUDE_DIR}/vendor/glad/glad.h
        ${PROJECT_INCLUDE_DIR}/vendor/stb/stb_image.h
        ${PROJECT_INCLUDE_DIR}/vendor/imgui/imgui.h
        ${PROJECT_INCLUDE_DIR}/vendor/imgui/imconfig.h
        ${PROJECT_INCLUDE_DIR}/vendor/imgui/imgui_internal.h
        ${PROJECT_INCLUDE_DIR}/vendor/imgui/imgui_textedit.h
        ${PROJECT_INCLUDE_DIR}/vendor/imgui/imgui_truetype.h
        ${PROJECT_INCLUDE_DIR}/vendor/imgui/imgui_rectpack.h
        ${PROJECT_INCLUDE_DIR}/vendor/imgui/imgui_impl_glfw.h
        ${PROJECT_INCLUDE_DIR}/vendor/imgui/imgui_impl_opengl3.h
        ${PROJECT_INCLUDE_DIR}/Light/light.h
        ${PROJECT_INCLUDE_DIR}/Light/ambientlight.h
        ${PROJECT_INCLUDE_DIR}/Light/directionallight.h
        ${PROJECT_INCLUDE_DIR}/Light/positionallight.h
        ${PROJECT_INCLUDE_DIR}/Light/pointlight.h
        ${PROJECT_INCLUDE_DIR}/Light/spotlight.h
        ${PROJECT_INCLUDE_DIR}/Application.h
        ${PROJECT_INCLUDE_DIR}/window.h
        ${PROJECT_INCLUDE_DIR}/system.h
        ${PROJECT_INCLUDE_DIR}/directory.h
        ${PROJECT_INCLUDE_DIR}/debugger.h
        ${PROJECT_INCLUDE_DIR}/shader.h
        ${PROJECT_INCLUDE_DIR}/vertexBuffer.h
        ${PROJECT_INCLUDE_DIR}/vertexArray.h
        ${PROJECT_INCLUDE_DIR}/vertexBufferLayout.h
        ${PROJECT_INCLUDE_DIR}/indexBuffer.h
        ${PROJECT_INCLUDE_DIR}/texture.h
        ${PROJECT_INCLUDE_DIR}/renderer.h
        ${PROJECT_INCLUDE_DIR}/mesh.h
        ${PROJECT_INCLUDE_DIR}/camera.h
        ${PROJECT_INCLUDE_DIR}/scene.h
        ${PROJECT_INCLUDE_DIR}/material.h
        ${PROJECT_INCLUDE_DIR}/model.h
        ${PROJECT_INCLUDE_DIR}/debugconsole.h
        ${PROJECT_INCLUDE_DIR}/assetmanager.h
        ${PROJECT_INCLUDE_DIR}/shadermanager.h
)

include_directories(${PROJECT_INCLUDE_DIR})
file(COPY ${PROJECT_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} )
set(GCC_COVERAGE_LINK_FLAGS "-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl ")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} ${PROJECT_VENDOR_DIR}/assimp-5.2.5/assimp-vc143-mtd.lib)
target_link_libraries(${PROJECT_NAME} ${PROJECT_VENDOR_DIR}/assimp-5.2.5/zlibstaticd.lib)