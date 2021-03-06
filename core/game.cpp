#include "game.hpp"
#include <chrono>
#include <thread>
#include "common/logger.hpp"
#include "common/time.hpp"
#include "ecs/ecs.hpp"
#include "ecs/system/system_register.hpp"
#include "service/service.hpp"
#include "world/world.hpp"
#include "common/random.hpp"

namespace game{

	void Game::Initialize(){
		SystemRegister::Initialize();
		World::Initialize(Random::NextInt());
		World::GenerateNew();
	}

	void Game::Stop(){
		state_ = EXITING;
	}

	void Game::ClearMemory(){
		SystemRegister::ClearMemory();
		ecs::ClearMemory();
		Service::ClearMemory();
	}

	void Game::Play(){
		state_ = RUNNING;

		while(state_ == RUNNING){
			Time::NotifyFrameStart();
			SystemRegister::Update();
			AdjustFrameRate();
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
