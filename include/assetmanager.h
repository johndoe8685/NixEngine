#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include "scene.h"
#include "Light/light.h"
#include "Light/ambientlight.h"
#include "Light/directionallight.h"
#include "Light/positionallight.h"
#include "Light/pointlight.h"
#include "Light/spotlight.h"
#include "shadowmap.h"

class AssetManager : public System
{
private:
	static AssetManager s_Instance;

	std::unordered_map<std::string, std::shared_ptr<Scene>> m_sceneMap;
	std::unordered_map<std::string, std::shared_ptr<AmbientLight>> m_AmbientLightMap;
	std::unordered_map<std::string, std::shared_ptr<DirectionalLight>> m_DirectionalLightMap;
	std::unordered_map<std::string, std::shared_ptr<PointLight>> m_PointLightMap;
	std::unordered_map<std::string, std::shared_ptr<SpotLight>> m_SpotLightMap;
	std::vector<std::shared_ptr<ShadowMap>> m_ShadowMapList;
	template<typename T> T* find(std::string componentName, std::unordered_map<std::string, std::shared_ptr<T>> map);
public:
	AssetManager();

	static AssetManager& Get() { return s_Instance; }

	void AddScene(std::string componentName);
	void AddAmbientLight(std::string componentName, glm::vec3 color, float ambientIntensity);
	void AddDirectionalLight(std::string componentName, glm::vec3 color, glm::vec3 direction, float ambientIntensity, float diffuseIntensity);
	void AddPointLight(std::string componentName, glm::vec3 color, glm::vec3 position, float ambientIntensity, float diffuseIntensity);
	void AddSpotLight(std::string componentName, glm::vec3 color, glm::vec3 position, glm::vec3 direction, float ambientIntensity, float diffuseIntensity, float edge);

	Scene* GetScene(std::string componentName);
	AmbientLight* GetAmbientLight(std::string componentName);
	DirectionalLight* GetDirectionalLight(std::string componentName);
	PointLight* GetPointLight(std::string componentName);
	SpotLight* GetSpotLight(std::string componentName);
	ShadowMap* GetShadowMap(size_t index);
	std::vector<std::shared_ptr<ShadowMap>>* GetShadowMapList();
};