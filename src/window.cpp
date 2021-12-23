#include "window.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); 
}
Window::Window()
{
    m_width = 800;
    m_height = 600;
}

Window::Window(int width, int height)
{
    m_width = width;
    m_height = height;
}

void Window::main()
{
    windowInitilaize(m_width, m_height);
    windowLoop();
}

void Window::windowInitilaize(int width, int height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mainWindow = glfwCreateWindow(width, height, "DENEME", NULL, NULL);
    if (mainWindow == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(mainWindow);

    //Use glad loader to load GL
    gladLoadGL();

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);
}


void Window::windowLoop()
{
    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

Window::~Window()
{
    glfwTerminate();
}
