#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
private:
    int m_height;
    int m_width;
    unsigned int m_ModuleID;
    GLFWwindow* mainWindow;
public:
    Window();
    Window(int width, int height);
    ~Window();
    bool getWindowShouldClose() { return glfwWindowShouldClose(mainWindow); }
    void main();
    void swapBuffers() { glfwSwapBuffers(mainWindow); }
    void windowInitilaize(int height, int width);
    void windowLoop();
};