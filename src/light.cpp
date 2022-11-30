#include "light.h"

int Light::m_PointLightIndex = 0;
int Light::m_SpotLightIndex = 0;
int	Light::m_CurrentPointSize = 0;
int Light::m_CurrentSpotSize = 0;

Light::Light()
	:m_color(glm::vec3(1.0f, 1.0f, 1.0f))
{
	
}

Light::Light(float red, float green, float blue)
:m_color(glm::vec3(red, green, blue))
{

}

void Light::useLight(Shader &shader)
{
	if (light == LightType::ambientLight)
	{
		struct ambientUniformList list;
		shader.SetUniform3f(list.m_colorName, m_color.x, m_color.y, m_color.z);
    	shader.SetUniform1f(list.m_ambientIntensityName, ambient.m_ambientIntensity);
	}
	else if(light == LightType::directionalLight)
	{
		struct directionalUniformList list;
		shader.SetUniform3f(list.m_colorName, m_color.x, m_color.y, m_color.z);
    	shader.SetUniform1f(list.m_ambientIntensityName, directional.m_ambientIntensity);
    
    	shader.SetUniform3f(list.m_directionName, directional.m_direction.x, directional.m_direction.y, directional.m_direction.z);
    	shader.SetUniform1f(list.m_diffuseIntensityName, directional.m_diffuseIntensity);
	}
	else if (light == LightType::pointLight)
	{
		shader.SetUniform3f(pointList.m_colorName, m_color.x, m_color.y, m_color.z);
		shader.SetUniform1f(pointList.m_ambientIntensityName, point.directional.m_ambientIntensity);
		shader.SetUniform1f(pointList.m_diffuseIntensityName, point.directional.m_diffuseIntensity);

		shader.SetUniform3f(pointList.m_positionName, point.m_position.x, point.m_position.y, point.m_position.z);
		shader.SetUniform1f(pointList.m_linearName, point.m_linear);
		shader.SetUniform1f(pointList.m_constantName, point.m_constant);
		shader.SetUniform1f(pointList.m_exponentName, point.m_exponent);
		
		shader.SetUniform1i(pointList.m_pointSizeName, point.m_pointSize);

		shader.SetPointLightInUse(1);
		shader.SetUniform1i(pointList.m_inUseName, shader.GetPointLightInUse());
	}
	else if (light == LightType::spotLight)
	{
		shader.SetUniform3f(spotList.m_colorName, m_color.x, m_color.y, m_color.z);
		shader.SetUniform1f(spotList.m_ambientIntensityName, spot.point.directional.m_ambientIntensity);
		shader.SetUniform1f(spotList.m_diffuseIntensityName, spot.point.directional.m_diffuseIntensity);

		shader.SetUniform3f(spotList.m_positionName, spot.point.m_position.x, spot.point.m_position.y, spot.point.m_position.z);
		shader.SetUniform1f(spotList.m_linearName, spot.point.m_linear);
		shader.SetUniform1f(spotList.m_constantName, spot.point.m_constant);
		shader.SetUniform1f(spotList.m_exponentName, spot.point.m_exponent);

		shader.SetUniform3f(spotList.m_directionName, spot.m_direction.x, spot.m_direction.y, spot.m_direction.z);
		shader.SetUniform1f(spotList.m_edgeName, spot.m_edge);
		shader.SetUniform1i(spotList.m_spotSizeName, spot.m_spotSize);
	}
}

void Light::stopLight(Shader& shader)
{
	if (light == LightType::ambientLight)
	{
		struct ambientUniformList list;
		shader.SetUniform3f(list.m_colorName, 0, 0, 0);
		shader.SetUniform1f(list.m_ambientIntensityName, 0);
	}
	else if (light == LightType::directionalLight)
	{
		struct directionalUniformList list;
		shader.SetUniform3f(list.m_colorName, 0, 0, 0);
		shader.SetUniform1f(list.m_ambientIntensityName, 0);

		shader.SetUniform3f(list.m_directionName, 0, 0, 0);
		shader.SetUniform1f(list.m_diffuseIntensityName, 0);
	}
	else if (light == LightType::pointLight)
	{
		shader.SetUniform3f(pointList.m_colorName, 0, 0, 0);
		shader.SetUniform1f(pointList.m_ambientIntensityName, 0);
		shader.SetUniform1f(pointList.m_diffuseIntensityName, 0);

		shader.SetUniform3f(pointList.m_positionName, 0, 0, 0);
		shader.SetUniform1f(pointList.m_linearName, 0);
		shader.SetUniform1f(pointList.m_constantName, 0);
		shader.SetUniform1f(pointList.m_exponentName, 0);

		shader.SetUniform1i(pointList.m_pointSizeName, 0);

		shader.SetUniform1i(pointList.m_inUseName, 0);
	}
	else if (light == LightType::spotLight)
	{
		shader.SetUniform3f(spotList.m_colorName, 0, 0, 0);
		shader.SetUniform1f(spotList.m_ambientIntensityName, 0);
		shader.SetUniform1f(spotList.m_diffuseIntensityName, 0);

		shader.SetUniform3f(spotList.m_positionName, 0, 0, 0);
		shader.SetUniform1f(spotList.m_linearName, 0);
		shader.SetUniform1f(spotList.m_constantName, 0);
		shader.SetUniform1f(spotList.m_exponentName, 0);

		shader.SetUniform3f(spotList.m_directionName, 0, 0, 0);
		shader.SetUniform1f(spotList.m_edgeName, 0);
		shader.SetUniform1i(spotList.m_spotSizeName, 0);
	}

}

void Light::setAsAmbientLight(float ambientIntensity)
{
    ambient.m_ambientIntensity = ambientIntensity;
	light = LightType::ambientLight;
}
void Light::setAsDirectionalLight(float ambientIntensity, float diffuseIntensity, float x, float y, float z)
{
	directional.m_ambientIntensity = ambientIntensity;
	directional.m_diffuseIntensity = diffuseIntensity;
	directional.m_direction = glm::vec3(x, y, z);
	light = LightType::directionalLight;

	m_lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}
void Light::setAsPointLight(float ambientIntensity, float diffuseIntensity, float x, float y, float z, float constant, float linear, float exponent)
{
	if (m_PointLightIndex > MAX_POINT_LIGHT) printf("Maximum point lights already initilaized.\n"); //debugger.giveMessage(Debugger::DebugLevel::Error, "setAsPointLight", "Maximum point lights already initilaized.");
	else
	{
		point.directional.m_ambientIntensity = ambientIntensity;
		point.directional.m_diffuseIntensity = diffuseIntensity;
		point.m_position = glm::vec3(x,y,z);
		point.m_constant = constant;
		point.m_linear = linear;
		point.m_exponent = exponent;
		point.m_inUse = 0;
		
		char Buffer[1024] = { "\0" };

		snprintf(Buffer, sizeof(Buffer), pointArrayList.m_colorName, m_PointLightIndex);
		pointList.m_colorName = Buffer;
		snprintf(Buffer, sizeof(Buffer), pointArrayList.m_ambientIntensityName, m_PointLightIndex);
		pointList.m_ambientIntensityName = Buffer;
		snprintf(Buffer, sizeof(Buffer), pointArrayList.m_diffuseIntensityName, m_PointLightIndex);
		pointList.m_diffuseIntensityName = Buffer;
		snprintf(Buffer, sizeof(Buffer), pointArrayList.m_positionName, m_PointLightIndex);
		pointList.m_positionName = Buffer;
		snprintf(Buffer, sizeof(Buffer), pointArrayList.m_constantName, m_PointLightIndex);
		pointList.m_constantName = Buffer;
		snprintf(Buffer, sizeof(Buffer), pointArrayList.m_linearName, m_PointLightIndex);
		pointList.m_linearName = Buffer;
		snprintf(Buffer, sizeof(Buffer), pointArrayList.m_exponentName, m_PointLightIndex);
		pointList.m_exponentName = Buffer;
		snprintf(Buffer, sizeof(Buffer), pointArrayList.m_inUseName, m_PointLightIndex);
		pointList.m_inUseName = Buffer;

		light = LightType::pointLight;
		m_PointLightIndex++;
		point.m_pointSize = m_PointLightIndex;
	}
}

void Light::setAsSpotLight(float ambientIntensity, float diffuseIntensity, float x, float y, float z, float constant, float linear, float exponent, glm::vec3 direction, float edge)
{
	if (m_SpotLightIndex > MAX_SPOT_LIGHT) printf("Maximum spot lights already initialized.\n"); //debugger.giveMessage(Debugger::DebugLevel::Error, "setAsSpotLight", "Maximum spot lights already initialized.");
	else
	{
		spot.point.directional.m_ambientIntensity = ambientIntensity;
		spot.point.directional.m_diffuseIntensity = diffuseIntensity;
		spot.point.m_position = glm::vec3(x, y, z);
		spot.point.m_constant = constant;
		spot.point.m_linear = linear;
		spot.point.m_exponent = exponent;
		spot.m_direction = glm::normalize(direction);
		spot.m_edge = cosf(glm::radians(edge));

		char Buffer[1024] = { "\0" };

		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_colorName, m_SpotLightIndex);
		spotList.m_colorName = Buffer;
		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_ambientIntensityName, m_SpotLightIndex);
		spotList.m_ambientIntensityName = Buffer;
		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_diffuseIntensityName, m_SpotLightIndex);
		spotList.m_diffuseIntensityName = Buffer;
		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_positionName, m_SpotLightIndex);
		spotList.m_positionName = Buffer;
		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_constantName, m_SpotLightIndex);
		spotList.m_constantName = Buffer;
		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_linearName, m_SpotLightIndex);
		spotList.m_linearName = Buffer;
		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_exponentName, m_SpotLightIndex);
		spotList.m_exponentName = Buffer;
		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_directionName, m_SpotLightIndex);
		spotList.m_directionName = Buffer;
		snprintf(Buffer, sizeof(Buffer), spotArrayList.m_edgeName, m_SpotLightIndex);
		spotList.m_edgeName = Buffer;
		
		light = LightType::spotLight;
		m_SpotLightIndex++;
		spot.m_spotSize = m_SpotLightIndex;
	}
}


void Light::setMovingLight(glm::vec3 position, glm::vec3 direction)
{
	spot.setFlash(position, direction);
}

bool Light::createShadowMap(int shadowWidth, int shadowHeight)
{
	if (light != LightType::spotLight) 
	{
		//debugger.giveMessage(Debugger::DebugLevel::Error, "Light::ShadowMap::Init", "Light type isnt supported.");
		return false;
	}
	else
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
	return m_lightProj * glm::lookAt(-directional.m_direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

Light::~Light()
{

}

