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
			void ProcessReceivedMessages();
			void AddGameObjectToDraw(GameObject*);
			Drawable* MakeGameObjectDrawable(GameObject*);
			void SetActiveCamera(GameObject*);
			glm::mat4 GetModelViewProjectionMatrixFor(Transform*);
			static void GLFWErrorCallback(int, const char*);

			std::vector<GameObject*> objects_to_render_;
			Camera* camera_;
			GLuint shader_;
			GLFWwindow* window_;
	};
}

#endif // GAME_CORE_SERVICES_RENDER_HPP
