#include "system_register.hpp"

namespace game{

	template<class T>
	T* SystemRegister::Get(){
		for(auto pair : systems_){
			if(pair.first == typeid(T)){
				return static_cast<T*>(pair.second);
			}
		}
		return nullptr;
	}

	template<class T>
	T* SystemRegister::CreateSystem(){
		T* system = Get<T>();
		if(system != nullptr){ return system; }

		system = new T();
		systems_.insert(std::pair<std::type_index, System*>(typeid(T), system));
		return system;
	}
}

