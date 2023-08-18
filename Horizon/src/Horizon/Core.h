/*
	Copyright (c) 2023 Noah Van Miert & TheCherno (Youtube series)
	Distributed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once

#include <memory>

#ifdef HR_PLATFORM_WINDOWS
#if HR_DYNAMIC_LINK
	#ifdef HR_BUILD_DLL
		#define HORIZON_API __declspec(dllexport)
	#else
		#define HORIZON_API __declspec(dllimport)
	#endif
#else
	#define HORIZON_API
#endif
#else
	#error Horizon only supports Windows for now!
#endif

#ifdef HR_DEBUG
	#define HR_ENABLE_ASSERTS
#endif

#ifdef HR_ENABLE_ASSERTS
	#define HR_ASSERT(x, ...)      { if(!(x)) { HR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HR_CORE_ASSERT(x, ...) { if(!(x)) { HR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HR_ASSERT(x, ...)
	#define HR_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HR_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Horizon {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}