#include "locator.hpp"

namespace game{

	template <class T>
	T* Locator::Get(){
		for( auto it = this->services_.begin();
			 it != this->services_.end();
			 it ++ ){

			if( it->first == typeid(T) ){
				T* service = static_cast<T*>(it->second);
				return service;
			}
		}
		return nullptr;
	}
}
