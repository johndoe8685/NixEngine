#pragma once
#include <iostream>
#include "window.h"
#include "vendor/imGui/imgui.h"
#include "vendor/imGui/imgui_impl_glfw.h"
#include "vendor/imGui/imgui_impl_opengl3.h"

enum DebugLevel
{
	Info,
	Warning,
	Error,
	Unknown
};

class Debugger
{
private:
	std::string m_className;
	DebugLevel m_DebugLevel;

	float m_x;
    float m_y;
    float m_z;
	float m_fov;
	bool m_Useflash;
	float m_deltaTime;
	float m_angle;
public:
	Debugger(std::string className);
	
	void giveMessage(DebugLevel level, std::string message);
	void giveMessage(DebugLevel level, std::string funcName, std::string message);

	//Imgui Debug Console
	void InitImgui(Window &window);
	void DebugConsole();
	float getFov() { return m_fov; };
	float getX() { return m_x; };
	float getY() { return m_y; };
	float getZ() { return m_z; };
	bool getUseFlash() { return m_Useflash; };
	float getAngle() { return m_angle; };
};