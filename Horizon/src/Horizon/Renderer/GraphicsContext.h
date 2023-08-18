/*
	Copyright (c) 2023 Noah Van Miert & TheCherno (Youtube series)
	Distributed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once

namespace Horizon {

	/* 
	   base class for graphics context, this will be implemented 
	   for every rendering api (OpenGL, Vulkan, DirectX11, Metal, ...)
	*/
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};

}