#include "Window.h"
#include<memory>
#include"Logging.h"


Window::Window(WindowData data)
	:data(data)
{
	m_Window = nullptr;
}

Window::~Window()
{

}


void Window::Create(std::string title)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	m_Window = glfwCreateWindow(data.width, data.height, title.c_str(), NULL, NULL);
	if (!m_Window)
	{
		LOG_ERROR("GLFW: Window failed to create", true);
	}
	LOG_INFO("GLFW: Window opened");

	Bind();
}


void Window::SetKeyCallback(void(*KeyCallback)(GLFWwindow*, int, int, int, int))
{
	glfwSetKeyCallback(m_Window, KeyCallback);
	LOG_INFO("GLFW: Set keycallback for window");
}

void Window::Bind()
{
	glfwMakeContextCurrent(m_Window);
}

GLFWwindow* Window::GetGLFWWindow()
{
	return m_Window;
}

void Window::Shutdown()
{
	glfwMakeContextCurrent(nullptr);
	glfwDestroyWindow(m_Window);
}

