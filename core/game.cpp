#include "game.hpp"
#include <chrono>
#include <thread>
#include "common/logger.hpp"
#include "common/time.hpp"
#include "ecs/ecs.hpp"
#include "service/service.hpp"
#include "world/world.hpp"
#include "ecs/system_register.hpp"

namespace game{

	void Game::Initialize(){
		World::GenerateNew();
		SystemRegister::Initialize();
	}

	void Game::Stop(){
		state_ = EXITING;
	}

	void Game::ClearMemory(){
		ECS::ClearMemory();
		Service::ClearMemory();
	}

	void Game::Play(){
		state_ = RUNNING;

		while(state_ == RUNNING){
			Time::NotifyFrameStart();
			SystemRegister::Update();
			AdjustFrameRate();
			//LOG(INFO) << "FPS : " << 1.f/Time::GetPreviousDeltaTime() << std::endl;
		}
		ClearMemory();
	}

	State Game::GetState(){
		return state_;
	}

	void Game::AdjustFrameRate(){
		long delay = (frame_duration_target_ - Time::GetCurrentFrameAdvance())*1000;
		if(delay <= 2){ return; }
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}

	State Game::state_ = UNINITIALIZED;
	float Game::frame_duration_target_ = 1.f/60.f;
}
