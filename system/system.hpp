#ifndef GAME_SERVICE_HPP
#define GAME_SERVICE_HPP

#include <vector>
#include "ecs/entity/entity.hpp"

namespace game{

	class System{
		public:
			System();
			System(float);
			virtual ~System() = 0;
			virtual void Update() final;
			virtual float GetExecutionTime() final;
			virtual void SetDesiredFrameDuration(float);

		protected:
			// The derived class must call this function to specify in which
			// entities it's interested in.
			template<class...Components>
			void Require();

			virtual void BeforeUpdate();
			virtual void OnUpdate(Entity);
			virtual void AfterUpdate();

		private:
			bool IsReadyToUpdate();

			float start_time_;
			float last_execution_time_;
			float target_frame_duration_;
			std::vector<Entity>(*get_matching_entities_)(); // Pointer to templated function
	};
}

#include "system.tcc"
#endif //GAME_SERVICE_HPP

