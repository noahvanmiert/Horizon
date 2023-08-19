/*
	Copyright (c) 2023 Noah Van Miert & TheCherno (Youtube series)
	Distributed under the MIT License (http://opensource.org/licenses/MIT)
*/

#include "hrpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Horizon {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:     HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLTexture2D>(path);
		}

		HR_CORE_ASSERT(false, "Unkown Renderer API!");
		return nullptr;
	}

}
