#include "stats.hpp"
#include "common/logger.hpp"
#include "common/time.hpp"

namespace game{

	DebugStats::DebugStats() : System(){}

	DebugStats::~DebugStats(){}

	void DebugStats::BeforeUpdate(){
		//LOG(INFO) << "FPS : " << 1.f/Time::GetPreviousDeltaTime() << std::endl;
	}
}
