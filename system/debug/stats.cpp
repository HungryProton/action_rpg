#include "stats.hpp"
#include "common/logger.hpp"
#include "common/time.hpp"

namespace game{

	DebugStats::DebugStats() : System(){
		min_ = -2;
		max_ = -1;
		avg_ = -1;
	}

	DebugStats::~DebugStats(){
		LOG(DEBUG) << "Min/Avg/Max : " << min_ << "/" << avg_ << "/" << max_ << std::endl;
	}

	void DebugStats::BeforeUpdate(){
		float current = 1.f/Time::GetPreviousDeltaTime();

		// trick to ignore the very first frame where all initialization takes place
		if(min_ == -2){ min_++; return; }
		if(min_ == -1){
			min_ = current;
			max_ = current;
			avg_ = current;
			return;
		}
		avg_ = avg_*0.9+current*0.1;
		if(current > max_){max_ = current;}
		if(current < min_){min_ = current;}
		//LOG(DEBUG) << current << std::endl;
	}
}
