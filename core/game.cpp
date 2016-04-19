#include "game.hpp"
#include <chrono>
#include <thread>
#include "common/logger.hpp"
#include "common/time.hpp"
#include "entity/system_register.hpp"
#include "entity/entity.hpp"

namespace game{

	void Game::Initialize(){
		SystemRegister::Initialize();
	}

	void Game::Stop(){
		state_ = EXITING;
	}

	void Game::ClearMemory(){
		SystemRegister::ClearMemory();
		Entity::ClearMemory();
	}

	void Game::Play(){
		state_ = RUNNING;

		while(state_ == RUNNING){
			Time::NotifyFrameStart();
			SystemRegister::Update();
			AdjustFrameRate();
			//LOG(INFO) << "FPS : " << 1.f/Time::GetDeltaTime() << std::endl;
		}
		ClearMemory();
	}

	State Game::GetState(){
		return state_;
	}

	void Game::AdjustFrameRate(){
		long delay = (frame_rate_target_ - Time::GetCurrentFrameAdvance())*1000;
		if(delay <= 2){ return; }
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}

	State Game::state_ = UNINITIALIZED;
	float Game::frame_rate_target_ = 1.f/30.f;
}
