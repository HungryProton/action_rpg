#include "walk_run.hpp"

namespace game{

	WalkRun::WalkRun() : WalkRun(1.f, 2.f){}

	WalkRun::WalkRun(float ws) : WalkRun(ws, 0.f){}

	WalkRun::WalkRun(float ws, float rs){
		walk_speed = ws;
		run_speed = rs;
	}
}
