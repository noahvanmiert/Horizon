/*
	Copyright (c) 2023 Noah Van Miert & TheCherno (Youtube series)
	Distributed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once

#include "Horizon/Renderer/Buffer.h"

#include <memory>

namespace Horizon {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};

}