/*
	Copyright (c) 2023 Noah Van Miert & TheCherno (Youtube series)
	Distributed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once

#include "Horizon/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>


namespace Horizon {

	class HORIZON_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()   { return s_CoreLogger;   }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}


#define HR_CORE_ERROR(...)    ::Horizon::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HR_CORE_WARN(...)     ::Horizon::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HR_CORE_INFO(...)     ::Horizon::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HR_CORE_TRACE(...)    ::Horizon::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HR_CORE_FATAL(...)    ::Horizon::Log::GetCoreLogger()->critical(__VA_ARGS__)


#define HR_ERROR(...)		  ::Horizon::Log::GetClientLogger()->error(__VA_ARGS__)
#define HR_WARN(...)		  ::Horizon::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HR_INFO(...)		  ::Horizon::Log::GetClientLogger()->info(__VA_ARGS__)
#define HR_TRACE(...)		  ::Horizon::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HR_FATAL(...)		  ::Horizon::Log::GetClientLogger()->critical(__VA_ARGS__)