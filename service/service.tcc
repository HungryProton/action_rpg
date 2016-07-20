#include "service.hpp"

namespace game{

	template<class T>
	T* Service::Get(){
		T* service = locator_.Get<T>();
		if(service == nullptr){ // Create service if don't exist yet
			service = Service::Create<T>();
		}
		return service;
	}

	template<class T>
	T* Service::Create(){
		T* service = new T();
		locator_.Transfer(service);
		return service;
	}
}
