#include "deps/catch.hpp"
#include "deps/fakeit.hpp"
#include "ecs/system/system_register.hpp"

namespace game{

	class SystemA : public System{ };

	class SystemRegisterStub : public SystemRegister{
		public:
			static void Initialize(){ SystemRegister::Initialize(); }
			static void ClearMemory(){ SystemRegister::ClearMemory(); }
			static int GetSystemCount(){ return systems_.size(); }
	};

	SCENARIO("SystemRegister should handle System related operations"){

		GIVEN("An empty SystemRegister"){
			SystemRegisterStub::ClearMemory();

			WHEN("A system is created"){
				SystemA* sa = SystemRegisterStub::CreateSystem<SystemA>();

				THEN("It should be possible to retrieve it"){
					SystemA* sa2 = SystemRegisterStub::Get<SystemA>();
					REQUIRE(sa2 == sa);
				}
				WHEN("We try to create another system with same type"){
					SystemA* new_sa = SystemRegisterStub::CreateSystem<SystemA>();

					THEN("It should return the already created system"){
						REQUIRE(new_sa == sa);
					}
				}
			}
			WHEN("The SystemRegister is manually initialized"){
				SystemRegisterStub::Initialize();

				THEN("It should have created all the systems required to play the game"){
					REQUIRE(SystemRegisterStub::GetSystemCount() > 1);
				}
				SystemRegisterStub::ClearMemory();
			}
		}
	}
}
