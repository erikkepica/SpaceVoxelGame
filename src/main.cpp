#include"Application/Application.h"



int main()
{
	std::unique_ptr<Application> app = std::make_unique<Application>(
		ApplicationData("SpaceVoxelGame")
	);

	app->Run();
	app->Shutdown();
}