#include "window.h"
#include "vendor/imGui/imgui.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
Window::Window()
:m_width(800), m_height(600), mouseFirstMoved(true), tabclicked(false), xChange(0), yChange(0)
{
    for(size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }
    Init(m_width, m_height);
}


Window::Window(int width, int height, Camera* camera)
:m_width(width), m_height(height), mouseFirstMoved(true), tabclicked(false), xChange(0), yChange(0), m_camera(camera)
{
    for(size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }
    Init(m_width, m_height);
}

void Window::Init(int width, int height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mainWindow = glfwCreateWindow(width, height, "NixEngine", NULL, NULL);
    if (mainWindow == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
    }

    //Set Current context
    glfwMakeContextCurrent(mainWindow);
    glfwSwapInterval(1);

    //Set Key and mouse input
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);

    //Check raw motion support if it's supported activate 
    if (glfwRawMouseMotionSupported())
    glfwSetInputMode(mainWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    
    //Locked the cursor to the window
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    //Use glad loader to load GL
    gladLoadGL();

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);
    glfwSetWindowUserPointer(mainWindow, this);
}


void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if(key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        if(!theWindow->tabclicked)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            theWindow->m_camera->setIsFocused(true);
            ImGui::SetWindowFocus(nullptr);
            theWindow->tabclicked = true;
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            theWindow->m_camera->setIsFocused(false);
            ImGui::SetWindowFocus("Nix Engine Debug Console");
            theWindow->tabclicked = false;
        }
    }
    if(key >= 0 && key < 1024)
    {
        if(action == GLFW_PRESS)
        {
            theWindow->keys[key] = true;
        }
        else if(action == GLFW_RELEASE)
        {
            theWindow->keys[key] = false;
        }
    }
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if(theWindow->mouseFirstMoved)
    {
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMoved = false;
    }

    theWindow->xChange = xPos - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - yPos;

    theWindow->lastX = xPos;
    theWindow->lastY = yPos;
}