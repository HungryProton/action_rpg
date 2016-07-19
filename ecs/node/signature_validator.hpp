#ifndef GAME_ECS_NODE_SIGNATURE_VALIDATOR_HPP_
#define GAME_ECS_NODE_SIGNATURE_VALIDATOR_HPP_

#include "ecs/entity/entity.hpp"

namespace game{

	class SignatureValidator{
		public:
			template<class... Components>
			static bool Validate(Entity);

		private:
			template<class T>
			static bool ValidateHelper(Entity);

			template<class T, class T2, class... Components>
			static bool ValidateHelper(Entity);
	};
}

#include "signature_validator.tcc"
#endif //GAME_ECS_NODE_SIGNATURE_VALIDATOR_HPP_
