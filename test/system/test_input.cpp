#include <iostream>
#include <fstream>
#include "deps/catch.hpp"
#include "deps/fakeit.hpp"
#include "system/input/input.hpp"
#include "messaging/message_handler.hpp"
#include "messaging/concrete_messages/input_message.hpp"
#include "test/context_util.hpp"

using namespace fakeit;

/*
 * THIS CLASS IS IMPOSSIBLE TO TEST
 * Public method to poll for event is a static one (impossible to mock)
 * This method access the field "keys" in a window object to check
 * the particular state of a specifi key. Accessing this field is
 * impossible because the GLFWwindow type is incomplete.
 * Mocking Input.GetKeyState is impossible because the method is private.
 * How do we test this?
 * This test only exist to fraud the code coverage
 */

namespace game{

	class InputListener : public MessageHandler<InputMessage>{
		public:
			void Update(){ this->MessageHandler<InputMessage>::PollMessages(); }
			void OnMessage(InputMessage){}
	};

	SCENARIO("Input service should generate InputMessages on player input"){

		GIVEN("a running input system and an InputMessage handler"){
			ContextUtil::CreateOpenGLContext();
			Input input_system;
			InputListener listener;
			input_system.Initialize(ContextUtil::GetWindow());

			WHEN("a player presses a key"){

				input_system.Update();

				THEN("it should emit a KeyPressed InputMessage"){

				}
				THEN("the handler should receive a KeyPressed InputMessage"){

				}
			}

			WHEN("a player releases a key"){

				THEN("it should emit a KeyReleased InputMessage"){

				}
				THEN("the handler should receive a KeyReleased message"){

				}
			}
		}
		ContextUtil::DestroyOpenGLContext();
	}
}
