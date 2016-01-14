#include "game.hpp"
#include "tools/logger.hpp"
#include "tools/time.hpp"
#include "core/locator/locator.hpp"
#include "core/service/input/input.hpp"
#include "core/service/render/render.hpp"
#include "core/service/logic/logic.hpp"

namespace game{

	// Create the core services.
	// /!\ CAUTION /!\ Instanciation order is important, main loop
	// will go through and ask services to update in this particular order
	void Game::Initialize(){

		// Create all services
		InstantiateCoreService<Input>();
		InstantiateCoreService<Logic>();
		InstantiateCoreService<Render>();

		// Initialize needed services
		// Input service needs a window (or a context) to capture user input
		Input* input = Locator::Get<Input>();
		Render* render = Locator::Get<Render>();
		Logic* logic = Locator::Get<Logic>();
		input->Initialize( render->GetWindow() );
		logic->Initialize();
	}

	void Game::Stop(){
		state_ = EXITING;
	}

	void Game::ClearMemory(){
		DeleteServices( &secondary_services_ );
		DeleteServices( &core_services_ );
	}

	void Game::Play(){
		state_ = RUNNING;

		while(state_ == RUNNING){
			Time::NotifyFrameStart();
			for(auto service : core_services_){
				service->Update();
			}
		}
		ClearMemory();
	}

	State Game::GetState(){
		return state_;
	}

	std::vector<CoreService*> Game::core_services_;
	std::vector<Service*> Game::secondary_services_;
	State Game::state_ = UNINITIALIZED;
}
