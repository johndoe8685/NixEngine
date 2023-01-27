#pragma once
#include "window.h"
//---Testing---
#include "assetmanager.h"
//---Testing---
#include "vendor/imGui/imgui.h"
#include "vendor/imGui/imgui_impl_glfw.h"
#include "vendor/imGui/imgui_impl_opengl3.h"
class DebugConsole
{
private:
	float m_x;
	float m_y;
	float m_z;
	float m_fov;
	float m_deltaTime;
	float m_angle;
	bool m_isFramebufferOpen;
	Window* m_window;
	//---Testing---
	AssetManager assetmanager;
	ShadowMap* testshadow;
	//---Testing---
public:
	float m_dx;
	float m_dy;
	float m_dz;
	FrameBuffer test;
	DebugConsole(Window* window);
	~DebugConsole();
	bool m_Useflash;
	bool m_UseDirectional;

	void Run();
	float getFov() { return m_fov; };
	float getX() { return m_x; };
	float getY() { return m_y; };
	float getZ() { return m_z; };
	float getAngle() { return m_angle; };
};