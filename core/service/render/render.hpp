#ifndef GAME_CORE_SERVICES_RENDER_HPP
#define GAME_CORE_SERVICES_RENDER_HPP

#include <vector>
#include <typeindex>
#include "tools/opengl.hpp"
#include "core/service/service.hpp"
#include "core/entity/game_object.hpp"
#include "core/messaging/message_handler.hpp"
#include "core/messaging/concrete_messages/rendering_intent.hpp"
#include "core/component/transform.hpp"
#include "core/component/camera.hpp"

namespace game{

	class Render : public CoreService,
								 public MessageHandler<RenderingIntent>{
		public:
			Render();
			~Render();

			void ClearMemory();
			void Update();

			GLFWwindow* GetWindow();

		private:
			void InitializeOpenGL();
			void InitializeGLFW();
			void InitializeGBuffer();
			void InitializeShaders();
			void ProcessReceivedMessages();
			void UpdateCamera();
			void RenderDrawingPool();
			void RenderQuad();
			void AddGameObjectToDraw(GameObject*);
			void ClearDrawingPool();
			Drawable* MakeGameObjectDrawable(GameObject*);
			void SetActiveCamera(GameObject*);
			glm::mat4 GetModelMatrixFor(Transform*,
				 								glm::vec3 local = glm::vec3(1.f, 1.f, 1.f));
			static void GLFWErrorCallback(int, const char*);

			std::vector<GameObject*> objects_to_render_;
			Camera* camera_;
			GLuint geometry_pass_shader_;
			GLuint lighting_pass_shader_;
			GLFWwindow* window_;

			// Defered render
			GLuint g_buffer_;
			GLuint g_position_;
			GLuint g_normal_;
			GLuint g_albedo_spec_;
			GLuint depth_buffer_;
			Drawable* quad_;
	};
}

#endif // GAME_CORE_SERVICES_RENDER_HPP
