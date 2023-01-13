#include "debugconsole.h"

DebugConsole::DebugConsole(Window* window)
    :m_window(window), test("test", 400, 300)
{
    assetmanager = AssetManager::Get();
    testshadow = assetmanager.GetShadowMap(0);
    m_x = 0.0f;
    m_y = 0.0f;
    m_z = -2.5f;
    m_fov = 90.0f;
    m_Useflash = false;
    m_UseDirectional = false;
    m_isFramebufferOpen = false;
    m_deltaTime = 0.0f;
    m_angle = 80.0f;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->getGLFWwindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

DebugConsole::~DebugConsole()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void DebugConsole::Run()
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
    ImGui::Checkbox("Directional Light", &m_UseDirectional);
    /*
    if (ImGui::Button("FrameBuffers"))
    {
        if (m_isFramebufferOpen) m_isFramebufferOpen = false;
        else m_isFramebufferOpen = true;
    }
    ImGui::End();
    if (m_isFramebufferOpen)
    {
        ImGui::Begin("FrameBuffers Window", &m_isFramebufferOpen);
        ImVec2 uv_min = ImVec2(0.0f, 1.0f);                 // Top-left
        ImVec2 uv_max = ImVec2(1.0f, 0.0f);                 // Lower-right
        ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
        ImVec4 border_col = ImVec4(0.2f, 0.3f, 0.3f, 1.0f); // 100% green
        ImGui::Image((ImTextureID)test.m_frameBufferTexture, ImVec2(test.m_textureWidth, test.m_textureHeight), uv_min, uv_max, tint_col, border_col);
        ImGui::End();
    }
    */
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
