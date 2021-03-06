#ifndef GAME_SYSTEM_RENDERER_HPP
#define GAME_SYSTEM_RENDERER_HPP

#include "../system.hpp"
#include "component/graphic/drawable.hpp"
#include "component/graphic/texture.hpp"
#include "component/graphic/mesh.hpp"
#include "component/transform.hpp"
#include "component/graphic/atlas.hpp"
#include "context_controller.hpp"
#include "shader_controller.hpp"
#include "drawable_builder.hpp"
#include "camera_controller.hpp"

namespace game{

	struct RenderComponent{
		Transform* transform;
		Texture* texture;
		Atlas* atlas;
		Mesh* mesh;
		Drawable* drawable;
		bool is_valid;
	};

	enum class LightType{POINT = 0, DIRECTIONAL, SPOT};
	struct glLight{
		LightType type;
		glm::vec3 color;
		float intensity;
		glm::vec3 vector;
	};

	class Renderer : public System{
		public:
			Renderer();
			~Renderer();

			GLFWwindow* GetWindow();

		protected:
			void BeforeUpdate();
			void OnUpdate(Entity);
			void AfterUpdate();

		private:
			RenderComponent GetComponentsFor(Entity);
			void ProcessLightIfAny(Entity);
			void SendLightsToShader();
			void ProcessTextures(RenderComponent);
			glm::mat4 GetModelMatrixFor(Transform*, glm::vec3);
			void UpdateCamera();
			void Draw(Drawable* drawable);
			void ApplyBlur(Program, int);

			ContextController context_controller_;
			ShaderController shader_controller_;
			DrawableBuilder drawable_builder_;
			CameraController camera_controller_;

			unsigned int max_lights;
			std::vector<glLight> lights_;
	};
}
#endif //GAME_SYSTEM_RENDERER_HPP
