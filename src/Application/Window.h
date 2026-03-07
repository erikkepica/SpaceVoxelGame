#pragma once
#include<GLFW/glfw3.h>
#include"Logging.h"

class WindowData
{
public:
	WindowData(int width, int height)
	{
		this->width= width;
		this->height = height;
	}

	int width;
	int height;
};

class Window
{
public:
	WindowData data;

	Window(WindowData data);
	~Window();

	void Create(std::string title);
	void SetKeyCallback(void (*KeyCallback)(GLFWwindow*, int, int, int, int));
	void Bind();
	GLFWwindow* GetGLFWWindow();

	void Shutdown();
private:
	GLFWwindow* m_Window;
};