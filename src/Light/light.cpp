#include "Light/light.h"

Light::Light(std::string componentName)
	:System(componentName, "Light"), m_color(glm::vec3(1.0f, 1.0f, 1.0f))
{
	shader = ShaderManager::Get().getShader("Basic");
}

Light::Light(std::string componentName, glm::vec3 color)
	:System(componentName, "Light"), m_color(color)
{
	shader = ShaderManager::Get().getShader("Basic");
}


bool Light::createShadowMap(int shadowWidth, int shadowHeight)
{

		m_ShadowWidth = shadowWidth;
		m_ShadowHeight = shadowHeight;
		glGenFramebuffers(1, &m_FBO);

		glGenTextures(1, &m_DepthMap);
		glBindTexture(GL_TEXTURE_2D, m_DepthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_ShadowWidth, m_ShadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthMap, 0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		unsigned int Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (Status != GL_FRAMEBUFFER_COMPLETE)
		{
			//debugger.giveMessage(Debugger::DebugLevel::Error, "createShadowMap::FrameBuffer", (const char*)Status);
			return false;
		}

		return true;
}


void Light::ShadowMapWrite()
{
	if (!m_FBO)
	{
		//debugger.giveMessage(Debugger::DebugLevel::Error, "Light::ShadowMap::Write", "FBO doenst exist.");
	}
	else
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);
	}
}

void Light::ShadowMapRead(unsigned int slot)
{
		if (!m_FBO)
		{
			//debugger.giveMessage(Debugger::DebugLevel::Error, "Light::ShadowMap::Write", "FBO doenst exist.");
		}
		else
		{
			glActiveTexture(slot);
			glBindTexture(GL_TEXTURE_2D, m_DepthMap);
		}
}

glm::mat4 Light::CalculateLightTransform()
{
	return glm::mat4(0.0f); //m_lightProj * glm::lookAt(-directional.m_direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

Light::~Light()
{

}

