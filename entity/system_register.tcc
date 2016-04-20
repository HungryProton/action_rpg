#include "system_register.hpp"

namespace game{

	template<class T>
	T* SystemRegister::CreateSystem(){
		for(auto pair : systems_){
			if(pair.first == typeid(T)){
				return static_cast<T*>(pair.second);
			}
		}
		T* system = new T();
		systems_.insert(std::pair<std::type_index, System*>(typeid(T), system));
	}

	template<class T>
	void SystemRegister::AssociateEntityTo(unsigned long id){
		for(auto pair : systems_){
			if(pair.first == typeid(T)){
				pair.second->AssociateEntity(id);
			}
		}
	}
}

