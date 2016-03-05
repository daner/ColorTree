#include <memory>
#include "Application.h"

using namespace ColorTree;

int main(int argc, char* argv[])
{
	auto app = std::make_unique<Application>();
	app->run();

	return 0;
}