#ifndef GAME_SERVICE_HPP
#define GAME_SERVICE_HPP

#include <vector>

namespace game{

	class System{
		public:
			System();
			virtual ~System() = 0;
			virtual void Update() final;
			virtual void AssociateEntity(Entity) final;
			virtual void DissociateEntity(Entity) final;
			virtual bool IsAssociatedWith(Entity) final;
			virtual float GetExecutionTime() final;

		protected:
			virtual void OnUpdate(Entity);
			virtual void BeforeUpdate();
			virtual void AfterUpdate();
			std::vector<Entity> associated_entities_;

		private:
			float start_time_;
			float last_execution_time_;
	};
}

#endif //GAME_SERVICE_HPP

