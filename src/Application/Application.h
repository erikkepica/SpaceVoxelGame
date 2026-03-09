#pragma once
#include"Application/Window.h"

class ApplicationData
{
public:
	ApplicationData()
	{
		name = "game";
	}
	ApplicationData(std::string name)
	{
		this->name = name;
	}

	std::string name;
};

class Application
{
public:
	Application(ApplicationData applicationData);

	void Create();

	void Run();

	void Shutdown();


	ApplicationData data;
private:
	void InitWindow(WindowData windowData);
	void CreateConsole();
	void InitGlfw();
	void InitGlad();
	void OpenGLSettings();

	std::shared_ptr<Window> m_Window;
};
