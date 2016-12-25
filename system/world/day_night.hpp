#ifndef GAME_SYSTEM_WORLD_DAY_NIGHT_HPP_
#define GAME_SYSTEM_WORLD_DAY_NIGHT_HPP_

#include <map>
#include "system/system.hpp"
#include "component/light/directional.hpp"

namespace game{

	class DayNightSystem : public System{
		public:
			DayNightSystem();
			~DayNightSystem();

		protected:
			void BeforeUpdate();
			void Initialize();
			void UpdateColor();

			Entity light_;
			DirectionalLight* dlight_;
			float day_duration_; //in seconds
			float night_duration_; //in seconds
			bool day_time_;
			std::map<int, glm::vec4> day_color_ramp_;	// angle (degree), color + power
			std::map<int, glm::vec4> night_color_ramp_;
	};
}

#endif //GAME_SYSTEM_WORLD_DAY_NIGHT_HPP_
