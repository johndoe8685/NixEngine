#include "renderer.h"

Renderer::Renderer(Window* window)
    :m_window(window), m_shadowMapSize(0), quadVAO(0)
{
    shadermanager = ShaderManager::Get();
    assetmanager = AssetManager::Get();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

Renderer::~Renderer()
{
    
}

void Renderer::DrawScene(Scene* scene)
{
    Shader* shader = shadermanager.getShader("Basic");
    ShadowMap* shadowMap = assetmanager.GetShadowMap(0);
    ProcessShadowMap(scene);

    //Geçici bir çözüm birden fazla shadow map kullanýldýðýnda deðiþtirilecek
    shader->SetUniformMatrix4fv("lightSpaceMatrix", shadowMap->GetLightSpaceMatrix());
    shader->SetUniform1f("ShadowMapBiasMin", shadowMap->m_biasMin);
    shader->SetUniform1f("ShadowMapBiasMax", shadowMap->m_biasMax);
    shader->SetUniform1i("aTexture", 0);
    shader->SetUniform1i("shadowMap", 1);

    scene->RenderScene(shadowMap, shader);
}

void Renderer::ProcessShadowMap(Scene* scene)
{
    glCullFace(GL_FRONT);
    std::vector<std::shared_ptr<ShadowMap>>* temp_shadowMapList = assetmanager.GetShadowMapList();
    m_shadowMapSize = temp_shadowMapList->size();
    Shader* shader = shadermanager.getShader("Shadow");
    for (size_t i = 0; i < m_shadowMapSize; i++)
    {
        scene->ProcessShadowMap(assetmanager.GetShadowMap(i), shader);
        scene->RenderScene(shader);
    }
    glCullFace(GL_BACK);
    GetDefaultFrameBuffer();
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.5f, 1.0f, 1.0f);
}

void Renderer::DepthDebug(Scene* scene)
{
    Shader* shader = shadermanager.getShader("DepthDebug");
    ProcessShadowMap(scene);
    shader->SetUniform1f("near_plane", 0.1f);
    shader->SetUniform1f("far_plane", 100.0f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, assetmanager.GetShadowMap(0)->m_frameBufferTexture);
    shader->Bind();
    renderQuad();
    shader->Unbind();
}

void Renderer::GetDefaultFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, m_window->getWidth(), m_window->getHeight());
    Clear();
}

void Renderer::renderQuad()
{

    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}