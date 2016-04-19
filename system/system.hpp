#ifndef GAME_SERVICE_HPP
#define GAME_SERVICE_HPP

#include <vector>

namespace game{

	class System{
		public:
			System();
			virtual ~System() = 0;
			virtual void Update() final;
			virtual void AssociateEntity(unsigned long);
			virtual float GetExecutionTime() final;
		protected:
			virtual void OnUpdate(unsigned long){}
			virtual void BeforeUpdate(){}
			std::vector<unsigned long> associated_entities_;
		private:
			float start_time_;
			float last_execution_time_;
	};
}

#endif //GAME_SERVICE_HPP

