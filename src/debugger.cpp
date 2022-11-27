#include "debugger.h"

Debugger::Debugger(std::string className)
    :m_className(className)
{
}

void Debugger::giveMessage(DebugLevel level, std::string message)
{
    switch (level)
    {
    case Info:
        std::cout << "[INFO]  " << message << std::endl;
        break;
    case Warning:
        std::cout << "[WARN]  " << message << std::endl;
        break;
    case Error:
        std::cout << "[ERROR] " << message << std::endl;
        break;
    case Unknown:
        std::cout << "[UNKWN] " << message << std::endl;
        break;
    default:
        break;
    }
}

void Debugger::giveMessage(DebugLevel level, std::string funcName, std::string message)
{
    switch (level)
    {
    case Info:
        std::cout << "[INFO]  " << "[" << funcName << "> " << message << std::endl;
        break;
    case Warning:
        std::cout << "[WARN]  " << "[" << funcName << "> " << message << std::endl;
        break;
    case Error:
        std::cout << "[ERROR] " << "[" << funcName << "> " << message << std::endl;
        break;
    case Unknown:
        std::cout << "[UNKWN] " << "[" << funcName << "> " << message << std::endl;
        break;
    default:
        break;
    }
}

void Debugger::InitImgui(Window &window)
{
    m_x = 0.0f;
    m_y = 0.0f;
    m_z = -2.5f;
    m_fov = 90.0f;
    m_Useflash = true;
    m_deltaTime = 0.0f;
    m_angle = 80.0f;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window.getGLFWwindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void Debugger::DebugConsole()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Nix Engine Debug Console");
    ImGui::Text("Nix Engine Debugging tool");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Text("[DeltaTime] %.6f", m_deltaTime);
    ImGui::Text("Positions of the object");
    ImGui::SliderFloat("X Position", &m_x, -1.0f, 1.0f);
    ImGui::SliderFloat("Y Position", &m_y, -1.0f, 1.0f);
    ImGui::SliderFloat("Z Position", &m_z, -2.5f, -5.0f);
    ImGui::SliderFloat("Speed", &m_angle, 0.0f, 360.0f);
    ImGui::SliderFloat("FOV", &m_fov, 5.0f, 120.0f);
    ImGui::Checkbox("FlashLight", &m_Useflash);
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
