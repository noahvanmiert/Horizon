/*
	Copyright (c) 2023 Noah Van Miert & TheCherno (Youtube series)
	Distributed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once

#include "Horizon/Core.h"

#include <string>

namespace Horizon {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};


	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};

}