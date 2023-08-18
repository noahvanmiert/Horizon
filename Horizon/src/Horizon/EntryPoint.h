/*
	Copyright (c) 2023 Noah Van Miert & TheCherno (Youtube series)
	Distributed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once


#ifdef HR_PLATFORM_WINDOWS


extern Horizon::Application* Horizon::CreateApplication();


int main(int argc, char** argv)
{
	Horizon::Log::Init();

	HR_CORE_INFO("logging system initialized");

	auto app = Horizon::CreateApplication();
	app->Run();
	delete app;
}


#endif