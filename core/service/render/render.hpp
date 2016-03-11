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
			void InitializeSSAO();
			void InitializeBloom();
			void InitializeLightFlare();
			void UpdateCamera();
			void RenderDrawingPool();
			void RenderQuad();
			void AddGameObjectToDraw(GameObject*);
			void ClearDrawingPool();
			Drawable* MakeGameObjectDrawable(GameObject*);
			void SetActiveCamera(GameObject*);
			glm::mat4 GetModelMatrixFor(Transform*,
				 								glm::vec3 local = glm::vec3(1.f, 1.f, 1.f));
			virtual void OnMessage(RenderingIntent);
			static void GLFWErrorCallback(int, const char*);

			std::vector<GameObject*> objects_to_render_;
			Camera* camera_;
			GLFWwindow* window_;
			int window_width_;
			int window_height_;

			// Defered render
			Drawable* quad_;
			GLuint g_buffer_;
			GLuint g_position_depth_;
			GLuint g_normal_;
			GLuint g_albedo_spec_;
			GLuint depth_buffer_;
			GLuint geometry_pass_shader_;
			GLuint lighting_pass_shader_;

			// SSAO
			GLuint ssao_buffer_;
			GLuint ssao_color_buffer_;
			GLuint ssao_blur_buffer_;
			GLuint ssao_blur_color_buffer_;
			GLuint noise_texture_;
			GLuint ssao_shader_;
			GLuint ssao_kernel_;

			// Generics
			GLuint monochromatic_blur_shader_;
			GLuint color_blur_shader_;
			GLuint high_contrast_shader_;

			// Bloom
			GLuint bloom_buffer_;
			GLuint bloom_color_buffer_;
			GLuint bloom_blur_buffer_;
			GLuint bloom_blur_color_buffer_;

			// Light flare
			GLuint light_flare_buffer_;
			GLuint light_flare_color_buffer_;
			GLuint light_flare_blur_buffer_;
			GLuint light_flare_blur_color_buffer_;
	};
}

#endif // GAME_CORE_SERVICES_RENDER_HPP
