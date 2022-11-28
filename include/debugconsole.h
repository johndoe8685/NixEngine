#pragma once
#include "window.h"
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
	bool m_Useflash;
	float m_deltaTime;
	float m_angle;
	Window* m_window;
public:
	DebugConsole(Window* window);
	~DebugConsole();

	void Run();
	float getFov() { return m_fov; };
	float getX() { return m_x; };
	float getY() { return m_y; };
	float getZ() { return m_z; };
	bool getUseFlash() { return m_Useflash; };
	float getAngle() { return m_angle; };
};