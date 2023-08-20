/*
	Copyright (c) 2023 Noah Van Miert & TheCherno (Youtube series)
	Distributed under the MIT License (http://opensource.org/licenses/MIT)
*/

#include <Horizon.h>

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public Horizon::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_BlockColor1(0.8f, 0.2f, 0.3f, 1.0f), m_BlockColor2(0.2f, 0.3f, 0.8f, 1.0f)
	{
		m_VertexArray.reset(Horizon::VertexArray::Create());

		float vertices[7 * 3] = {
			-0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.9f, 0.1f, 0.3f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.4f, 0.0f, 1.0f,
		};

		Horizon::Ref<Horizon::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Horizon::VertexBuffer::Create(vertices, sizeof(vertices)));

		Horizon::BufferLayout layout = {
			{ Horizon::ShaderDataType::Float3, "a_Position" },
			{ Horizon::ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Horizon::Ref<Horizon::IndexBuffer> indexBuffer;
		indexBuffer.reset(Horizon::IndexBuffer::Create(indices, sizeof(vertices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Horizon::VertexArray::Create());

		float vertices2[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		Horizon::Ref<Horizon::VertexBuffer> squareVB;
		squareVB.reset(Horizon::VertexBuffer::Create(vertices2, sizeof(vertices2)));

		squareVB->SetLayout({
			{ Horizon::ShaderDataType::Float3, "a_Position" },
			{ Horizon::ShaderDataType::Float2, "a_TexCoord"}
		});

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t indices2[6] = { 0, 1, 2, 2, 3, 0 };
		Horizon::Ref<Horizon::IndexBuffer> squareIB;
		squareIB.reset(Horizon::IndexBuffer::Create(indices2, sizeof(vertices2) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Horizon::Shader::Create(vertexSrc, fragmentSrc));

		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_Shader2.reset(Horizon::Shader::Create(vertexSrc2, fragmentSrc2));

		m_TextureShader.reset(Horizon::Shader::Create("C:/dev/Horizon/Sandbox/src/assets/shaders/Texture.glsl"));

		m_Texture = Horizon::Texture2D::Create("C:/dev/Horizon/Sandbox/src/assets/textures/Checkerboard.png");
		m_ChernoLogo = Horizon::Texture2D::Create("C:/dev/Horizon/Sandbox/src/assets/textures/Chernologo.png");

		std::dynamic_pointer_cast<Horizon::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Horizon::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}


	void OnUpdate(Horizon::DeltaTime deltaTime) override
	{
		using Horizon::Input;
		using Horizon::RenderCommand;
		using Horizon::Renderer;

		if (Input::IsKeyPressed(HR_KEY_A))
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0.5f * deltaTime, 0.0f, 0.0f));

		else if (Input::IsKeyPressed(HR_KEY_D))
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(-0.5f * deltaTime, 0.0f, 0.0f));

		else if (Input::IsKeyPressed(HR_KEY_W))
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0.0f, -0.5f * deltaTime, 0.0f));

		else if (Input::IsKeyPressed(HR_KEY_S))
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0.0f, 0.5f * deltaTime, 0.0f));

		else if (Input::IsKeyPressed(HR_KEY_Q))
			m_Camera.SetRotation(m_Camera.GetRotation() + (5.0f * deltaTime));

		else if (Input::IsKeyPressed(HR_KEY_E))
			m_Camera.SetRotation(m_Camera.GetRotation() - (5.0f * deltaTime));


		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::Clear();

		Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Horizon::OpenGLShader>(m_Shader2)->Bind();
		std::dynamic_pointer_cast<Horizon::OpenGLShader>(m_Shader2)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++) 
		{
			for (int x = 0; x < 20; x++) 
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Renderer::Submit(m_Shader2, m_SquareVA, transform);
			}
		}
		 
		m_Texture->Bind();
		Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
		m_ChernoLogo->Bind();
		Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Renderer::Submit(m_Shader, m_VertexArray);

		Renderer::EndScene();
	}


	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();
	}


	void OnEvent(Horizon::Event& event) override
	{
	}

private:
	Horizon::Ref<Horizon::Shader> m_Shader;
	Horizon::Ref<Horizon::VertexArray> m_VertexArray;

	Horizon::Ref<Horizon::Shader> m_Shader2, m_TextureShader;
	Horizon::Ref<Horizon::VertexArray> m_SquareVA;

	Horizon::Ref<Horizon::Texture2D> m_Texture;
	Horizon::Ref<Horizon::Texture2D> m_ChernoLogo;

	glm::vec4 m_BlockColor1;
	glm::vec4 m_BlockColor2;

	Horizon::OrthoGraphicCamera m_Camera;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};


class Sandbox : public Horizon::Application 
{
public:

	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};


Horizon::Application* Horizon::CreateApplication()
{
	return new Sandbox();
}