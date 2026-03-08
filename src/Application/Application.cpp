#include"Application/Application.h"
#include"glad/glad.h"
#include"Universe/Universe.h"

Application::Application(ApplicationData applicationData)
{
	this->data = applicationData;
	Create();
}

void Application::Create()
{
	CreateConsole();
	InitGlfw();
	InitWindow(WindowData(512, 300));
	InitGlad();
	OpenGLSettings();
}



void Application::InitWindow(WindowData windowData)
{
	m_Window = std::make_unique<Window>(windowData);
	m_Window->Create(data.name);
}

void Application::CreateConsole()
{
#ifdef _WIN32
#ifdef _MSC_VER 
#if DEVELOPMENT_BUILD == 0
	AllocConsole();
	(void)freopen("conin$", "r", stdin);
	(void)freopen("conout$", "w", stdout);
	(void)freopen("conout$", "w", stderr);
	std::cout.sync_with_stdio();
#endif
#endif
#endif

}

void error_callback(int error, const char* description)
{
	LOG_ERROR("GLFW: " << error << ", " << description, false);
}


void Application::InitGlfw()
{
	if (!glfwInit())
	{
		LOG_ERROR("GLFW: Failed to initialize", true);
	}
	LOG_INFO("GLFW: Initialized");
	glfwSetErrorCallback(error_callback);
}

void Application::InitGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_ERROR("GLAD: Failed to initialize", true);
	}
	LOG_INFO("GLAD: Initialized");
}

void Application::Shutdown()
{
	m_Window->Shutdown();
}

void Application::OpenGLSettings()
{
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}









void Application::Run()
{
	Universe universe;

	float lastFrame = 0;

	while (!glfwWindowShouldClose(m_Window->GetGLFWWindow()))
	{
		float deltaTime = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();

		glfwPollEvents();
		int width, height;

		glfwGetFramebufferSize(m_Window->GetGLFWWindow(), &width, &height);
		m_Window->data.width = width;
		m_Window->data.height = height;


		glViewport(0, 0, width, height);
		glClearColor(28.f/255, 31.f/255, 36.f/255, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		universe.Render(m_Window->data);
		universe.Update(deltaTime);

		glfwSwapBuffers(m_Window->GetGLFWWindow());
	}
}