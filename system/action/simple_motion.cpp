#include "simple_motion.hpp"
#include "component/transform.hpp"
#include "component/action/simple_motion.hpp"

namespace game{

	SimpleMotionSystem::SimpleMotionSystem() : System(){
		Require<Transform, SimpleMotion>();
	}

	void SimpleMotionSystem::OnUpdate(Entity entity){
		
	}
}
