#pragma once
#include <iostream>
#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>
#include "vendor/imGui/imgui.h"
#include "vendor/imGui/imgui_impl_glfw.h"
#include "vendor/imGui/imgui_impl_opengl3.h"
#include "camera.h"
#include "shadermanager.h"

class Window
{
private:
    unsigned int m_ModuleID;
    
    int m_height;
    int m_width;
    double lastX, lastY;
    double xChange, yChange;

    float m_curFrame, m_lastFrame;

    bool keys[1024];
    bool mouseFirstMoved;
    bool tabclicked;

    GLFWwindow* mainWindow;
    Camera* m_current_camera;
    ShaderManager shadermanager;
public:
    Window();
    Window(int width, int height);
    Window(int width, int height, Camera* camera);
    ~Window() { glfwTerminate(); }

    void Init(int height, int width);

    void SetCamera(Camera* camera);
    void SwapBuffers() { glfwSwapBuffers(mainWindow); }
    bool GetWindowShouldClose();
    void getSize() { glfwGetWindowSize(mainWindow, &m_width, &m_height); }
    int getHeight() { getSize(); return m_height; }
    int getWidth() { getSize(); return m_width; }
    void setHeight(int height) { m_height = height; };
    void setWidth(int width) { m_width = width; };
    double getXChange() { double theChange = xChange; xChange = 0.0f; return theChange; }
    double getYChange() { double theChange = yChange; yChange = 0.0f; return theChange; }
    bool* getKeys() { return keys; }
    GLFWwindow* getGLFWwindow() { return mainWindow; }

private:
    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};