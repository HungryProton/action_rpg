#include "locator.hpp"
#include "service/service.hpp"
#include "service/service_worker.hpp"

namespace game{

	void Locator::Transfer(ServiceWorker* service){
		this->services_.insert( std::pair<std::type_index, ServiceWorker*>(
									   typeid(*service), service) );
	}

	void Locator::ClearMemory(){
		for(auto pair : this->services_){
			delete pair.second;
		}
		this->services_.clear();
	}
}
