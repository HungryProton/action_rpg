#include "system_register.hpp"
#include "system/input/input.hpp"
//#include "system/physic/physic.hpp"
#include "system/renderer/renderer.hpp"
#include "system/gui/gui.hpp"

namespace game{

	// Create the systems
	// /!\ CAUTION /!\ Instanciation order is important, main loop
	// will go through and ask systems to update in this particular order
	void SystemRegister::Initialize(){
		CreateSystem<Input>();
		//CreateSystem<Physic>();
		CreateSystem<Gui>();
		CreateSystem<Renderer>();

		Input* input = Get<Input>();
		Renderer* renderer = Get<Renderer>();

		input->Initialize(renderer->GetWindow());
	}

	void SystemRegister::Update(){
		for(auto pair : systems_){
			pair.second->Update();
		}
	}

	void SystemRegister::ClearMemory(){
		for(auto pair : systems_){
			delete pair.second;
		}
		systems_.clear();
	}

	std::map<std::type_index, System*> SystemRegister::systems_;
}
