#include "system_register.hpp"

#include "system/input/input.hpp"
#include "system/physic/physic.hpp"
#include "system/renderer/renderer.hpp"

namespace game{

	// Create the systems
	// /!\ CAUTION /!\ Instanciation order is important, main loop
	// will go through and ask systems to update in this particular order
	void SystemRegister::Initialize(){
		CreateSystem<Input>();
		CreateSystem<Physic>();
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

	void SystemRegister::DissociateEntityFromAll(unsigned long id){
		for(auto pair : systems_){
			pair.second->DissociateEntity(id);
		}
	}

	void SystemRegister::CloneAssociationOfInto(unsigned long original, unsigned long clone){
		for(auto pair : systems_){
			if(pair.second->IsAssociatedWith(original)){
				pair.second->AssociateEntity(clone);
			}
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
