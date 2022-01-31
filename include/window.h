#pragma once
#include <iostream>
#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
private:
    int m_height;
    int m_width;
    unsigned int m_ModuleID;
    GLFWwindow* mainWindow;
public:
    Window();
    Window(int width, int height);
    ~Window() { glfwTerminate(); }


    void Init(int height, int width);

    void SwapBuffers() { glfwSwapBuffers(mainWindow); }
    bool GetWindowShouldClose() { return glfwWindowShouldClose(mainWindow); }
};