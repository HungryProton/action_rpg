#ifndef GAME_SYSTEM_RENDERER_HPP
#define GAME_SYSTEM_RENDERER_HPP

#include "../system.hpp"
#include "component/drawable.hpp"
#include "component/texture.hpp"
#include "component/mesh.hpp"
#include "component/transform.hpp"
#include "context_controller.hpp"
#include "shader_controller.hpp"
#include "drawable_builder.hpp"
#include "camera_controller.hpp"

namespace game{

	struct RenderComponent{
		Transform* transform;
		Texture* texture;
		Mesh* mesh;
		Drawable* drawable;
		bool is_valid;
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
			glm::mat4 GetModelMatrixFor(Transform*, glm::vec3);
			void UpdateCamera();
			void Draw(Drawable* drawable);

			ContextController context_controller_;
			ShaderController shader_controller_;
			DrawableBuilder drawable_builder_;
			CameraController camera_controller_;
	};
}
#endif //GAME_SYSTEM_RENDERER_HPP